#ifndef PAGE_H
#define PAGE_H

struct page {
	int id;
	int present;
	int entered;
};

struct page new_page();

#endif
