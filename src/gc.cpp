#include "gc.h"

::gc::Header::Header() : prev(this), next(this) {
}

void
::gc::insert_before(::gc::Header&new_header, Header&header) {
  new_header.prev = header.prev;
  new_header.next = &header;
  header.prev->next = &new_header;
  header.prev = &new_header;
}

void
::gc::remove(::gc::Header& header) {
  header.prev->next = header.next;
  header.next->prev = header.prev;
}

::gc::Context::Context() : header() {
}

::gc::Context::~Context() {
  collect();
}

void
::gc::Context::collect() {
  ::gc::Header unused;

  for (::gc::Header *p=&header; p->next != &header; p = p->next) {
    ::gc::Object *object = (::gc::Object *)(p->next);

    for(size_t i=0; i< object->info->n; i++) {
      ::gc::Object **base = (::gc::Object **)((object->payload) + object->info->offsets[i]);
      for(size_t j=0; j< object->info->sizes[i]; j++) {
        base[j]->ref_count --;
      }
    }
  }

  for(::gc::Header *p=header.next, *next=p->next; p != &header; p = next, next = next->next) {
    ::gc::Object *object = (::gc::Object *)p;
    if (object->ref_count > 0)
      continue;
    remove(object->header);
    insert_before(object->header, unused);
  }

  for(::gc::Header *p=header.next; p != &header; p = p->next) {
    ::gc::Object *object = (::gc::Object *)p;

    for(size_t i=0; i< object->info->n; i++) {
      ::gc::Object **base = (::gc::Object **)((object->payload) + object->info->offsets[i]);
      for(size_t j=0; j< object->info->sizes[i]; j++) {
        if(base[j]->ref_count == 0) {
          remove(base[j]->header);
          insert_before(base[j]->header, header);
        }
        base[j]->ref_count ++;
      }
    }
  }

  for(::gc::Header *p=unused.next; p != &unused; p = p->next) {
    ::gc::Object *object = (::gc::Object *)p;
    object->info->destroy(object->payload);
  }

  for(::gc::Header *p=unused.next, *next=p->next; p != &unused; p = next, next = next->next) {
    ::std::free((::gc::Object *)p);
  }
}

void
::gc::collect(::gc::Context& context) {
  return context.collect();
}
