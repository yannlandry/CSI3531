#include "page.h"

struct page new_page(int id) {
	struct page p;
	p.id = id;
	p.present = 0;
	p.entered = 0;
	return p;
}
