#pragma once

#include <algorithm>

namespace meta {
  using size_t = ::std::size_t;

#ifdef __GNUC__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wnon-template-friend"
#endif

  template<typename T, size_t>
  struct getter {
    friend auto _meta_state(getter);
  };

#ifdef __GNUC__
#   pragma GCC diagnostic pop
#endif

  template<typename T, typename U, size_t N>
  struct setter {
    friend auto _meta_state(getter<T, N>) {
      return U {};
    }
  };

  template<typename T, size_t N=0, typename =decltype([]{})>
  constexpr
  size_t
  next() {
    if constexpr (requires (getter<T, N> r) { _meta_state(r); }) {
      return next<T, N+1>();
    } else {
      return N;
    }
  }

  template<typename T, size_t N=next<T>()>
  using get = ::std::enable_if_t<(N>0), decltype(_meta_state(getter<T, N-1>{}))>;

  template<typename T, typename U, size_t N=next<T>()>
  consteval
  bool
  set() {
    (void)sizeof(setter<T, U, N>);
    return true;
  };

  template<auto V>
  struct value {
  };

  template<typename... T>
  struct list {
  };

  template<typename T, typename U>
  struct append;

  template<typename U, typename... T>
  struct append<list<T...>, U> {
    using type = list<T..., U>;
  };

  template<typename T, typename U>
  using append_t = append<T, U>::type;
}

namespace type_traits {
  template<typename T>
  struct class_of;

  template<typename T, typename U>
  struct class_of<U T::*> {
    using type = T;
  };

  template<typename T>
  using class_of_t = class_of<T>::type;

  template<typename T>
  struct remove_class;

  template<typename T, typename U>
  struct remove_class<U T::*> {
    using type = U;
  };

  template<typename T>
  using remove_class_t = remove_class<T>::type;
}

namespace gc {
  using size_t = ::std::size_t;
  template<typename T, size_t = sizeof(T)>
  constexpr
  bool
  is_defined(int) {
    return true;
  }

  template<typename T>
  constexpr
  bool
  is_defined(...) {
    return false;
  }

  struct ClassInfo {
    void (*destroy)(void *);
    size_t n;
    size_t const *offsets;
    size_t const *sizes;
  };

  template<typename T>
  struct ClassData {
    static const ClassInfo info;
  };

  template<typename T>
  void
  destroy(void *p) {
    ((T *)p)->~T();
  }

  struct Header {
    Header *prev, *next;

    Header();
  };

  void
  insert_before(Header&new_header, Header&header);

  void
  remove(Header& header);

  struct Object {
    Header header;
    ClassInfo const *info;
    size_t ref_count;
    char payload[];
  };

  template<typename T>
  struct ptr {
    Object *object;

    ptr(Object *object = nullptr) : object(object) {
      increase();
    }

    ptr(ptr const& other) : object(other.object) {
      increase();
    }

    ptr(ptr&& other) noexcept : object(nullptr) {
      ::std::swap(object, other.object);
    }

    operator bool() const {
      return !(object == nullptr);
    }

    T &
    operator*() {
      return *((T*)(object->payload));
    }

    T const&
    operator*() const {
      return *((T*)(object->payload));
    }

    T *
    operator->() {
      return ((T*)(object->payload));
    }

    T const*
    operator->() const {
      return ((T*)(object->payload));
    }

    ptr&
    operator=(ptr const& other) {
      decrease();
      object = other.object;
      increase();
      return *this;
    }

    ptr&
    operator=(ptr&& other) noexcept {
      ::std::swap(object, other.object);
      return *this;
    }

    void
    increase() {
      if (object)
        object->ref_count++;
    }

    void
    decrease() {
      if(!object)
        return;
      if(--(object->ref_count) > 0)
        return;

      remove(object->header);
      destroy<T>(object->payload);
      ::std::free(object);
    }

    ~ptr() {
      decrease();
    }

  };

  template<typename T>
  struct is_ptr;

  template<typename T>
  struct is_ptr<ptr<T>> {
    static const bool value = true;
  };

  template<typename T>
  struct is_ptr {
    static const bool value = false;
  };

  template<typename T>
  constexpr
  bool is_ptr_v = is_ptr<T>::value;

  template<typename T>
  struct _MemberList;

  template<auto... members>
  struct _MemberList<::meta::list<::meta::value<members>...>> {
    static const size_t n = sizeof...(members);
    static size_t offsets[sizeof...(members)];
    static size_t sizes[sizeof...(members)];
  };

  template<auto... members>
  size_t _MemberList<::meta::list<::meta::value<members>...>>::offsets[sizeof...(members)] = {
    reinterpret_cast<std::size_t>(&(((type_traits::class_of_t<decltype(members)>*)0)->*members))... };

  template<auto... members>
  size_t _MemberList<::meta::list<::meta::value<members>...>>::sizes[sizeof...(members)] = {
    sizeof(type_traits::remove_class_t<decltype(members)>)/sizeof(void*)... };

  template<
    typename T,
    size_t =sizeof(T),
    typename =::std::enable_if_t<(::meta::next<ptr<T>>() > 0)>>
  ::gc::_MemberList<::meta::get<ptr<T>>>
  get_members();

  template<
    typename T,
    size_t =sizeof(T),
    typename =::std::enable_if_t<(::meta::next<ptr<T>>() == 0)>>
  ::gc::_MemberList<::meta::list<>>
  get_members();

  template<typename T>
  const
  ClassInfo
  ClassData<T>::info = {
    .destroy = &destroy<T>,
    .n = decltype(get_members<T>())::n,
    .offsets = decltype(get_members<T>())::offsets,
    .sizes = decltype(get_members<T>())::sizes,
  };

  template <auto member, typename =decltype([]{})>
  consteval
  bool
  declare_member() {
    using M = decltype(member);
    using T = type_traits::class_of_t<M>;
    using U = type_traits::remove_class_t<M>;
    using P = ptr<T>;

    static_assert(not is_defined<T>(0));
    static_assert(is_ptr_v<::std::remove_all_extents_t<U>>);
    return ::meta::set<P, ::meta::append_t<::meta::get<P>, ::meta::value<member>>>();
  }


  struct Context {
    Header header;

    Context();

    template<typename T>
    ptr<T>
    make(T&& value) {
      Object *object = (Object*)::std::malloc(sizeof(Object) + sizeof(T));
      object->info = &(ClassData<T>::info);
      object->ref_count = 0;
      new (object->payload) T(::std::move(value));
      insert_before(object->header, header);
      return object;
    }

    void
    collect();

    ~Context();
  };

  static Context default_context;

  template<typename T>
  ptr<T>
  make(T&& value, Context& context = default_context) {
    return context.make(::std::move(value));
  }

  void
  collect(Context& context = default_context);
}

#define GC_OBJECT(T)                                            \
  using __TYPE__ = T;                                           \
  static_assert(not ::gc::is_defined<T>(0));                    \
  static_assert(::meta::set<::gc::ptr<T>, ::meta::list<>>());   \

#define _GC_MEMBER_1(name, shape) name shape
#define _GC_MEMBER_0(name) name
#define _GC_MEMBER(x,y,M,...) M
#define GC_MEMBER(name, ...)                                            \
  _GC_MEMBER(,##__VA_ARGS__, _GC_MEMBER_1, _GC_MEMBER_0)(name,##__VA_ARGS__); \
  static_assert(::gc::declare_member<&__TYPE__::name>())               \

