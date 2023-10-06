#include <stdlib.h>
#include <time.h>
#include "pch.h"
#include <iostream>
using namespace std;

struct m_list {
	int inf;
	m_list * next;
};

void zapolnenie(int n_elementov, m_list * &first) {
	m_list *p = first;
	first = new m_list;
	p = first;
	p->inf = rand() % 10;
	for (int i = 0; i < n_elementov - 1; i++) {
		p->next = new m_list;
		p = p->next;
		p->inf = rand() % 10;
	}
	p->next = 0;
	p=first;
}

void pechat(m_list * &first) {
	m_list *p = first;
	while (p) {
		cout << p->inf << endl;
		p = p->next;
	}
}

void ERROR() {
	cout << "ERROR :)"<< endl;
}

void vstvka_v_nachalo(m_list * &first, m_list * &q_v_nachalo) {
	m_list *p = first;
	p = first;
	if (first==0) {
		q_v_nachalo->inf = rand() % 10;
		first = q_v_nachalo;
	}
	q_v_nachalo->next = first;
	first = q_v_nachalo;
	p = first;
}

void vstavka_v_konec(m_list * &first, m_list * & t) {
	m_list *p = first;
	p = first;
	while (p) {
		if (p->next == 0) {
			p->next = t;
			t->next = 0;
		}
		p = p->next;
	}
	p = first;
}

void vstavka_posle_i(int k_posle_i, m_list * &first, m_list * &w_posle_i) {
	m_list *p = first;
	p = first;
	int S = 0;
	while (p) {
		p = p->next;
		S++;
	}
	p = first;

	if (k_posle_i > S+1) {
		ERROR();
		return;
	}
	if (S == k_posle_i) {
		vstavka_v_konec(first, w_posle_i);
		return;
	}
	if (k_posle_i == 0) {
		vstvka_v_nachalo(first, w_posle_i);
		return;
	}
	if (first==0) {
		w_posle_i->inf = rand() % 10;
		first = w_posle_i;
		return;
	}

	for (int i = 0; i < k_posle_i-1; i++) {
		p = p->next;
	}
	w_posle_i->next = p->next;
	p->next = w_posle_i;
	p = first;
}

void vstavka_pered_i(int k_pered_i, m_list * &first, m_list * &w_pered_i) {
	m_list *p = first;
	p = first;
	int S = 1;
	while (p) {
		p = p->next;
		S++;
	}
	p = first;

	if (first==0) {
		w_pered_i->inf = rand() % 10;
		first = w_pered_i;
	}
	if (k_pered_i <= 0) {
		ERROR();
		return;
	}
	if (k_pered_i > S+1) {
		ERROR();
		return;
	}
	if (k_pered_i == 1) {
		vstvka_v_nachalo(first, w_pered_i);
		return;
	}
	for (int i = 1; i < k_pered_i - 1; i++) {
		p = p->next;
	}
	w_pered_i->next = p->next;
	p->next = w_pered_i;
	p = first;
}

void ydalenie_pervogo_elementa(m_list * &first, m_list * &w_ydalenie) {
	m_list *p = first;
	w_ydalenie = first;
	first = p->next;
	delete w_ydalenie;
	p = first;
}

void ydalenie_poslednego_elementa(m_list * &first, m_list * &w_ydalenie) {
	m_list *p = first;
	while ((p->next)->next) {
		p = p->next;
	}
	w_ydalenie = p->next;
	p->next = 0;
	delete w_ydalenie;
	p = first;
}

void ydalenie_i_elementa(int k_ydalenie, m_list * &first) {
	m_list *p = first;
	m_list *w_ydalenie;
	int k = 1;
	while (p) {
		if (k_ydalenie == 1) {
			ydalenie_pervogo_elementa(first, w_ydalenie);
			return;
		}
		if (k_ydalenie -1 == k) {
			w_ydalenie = p->next;
			p->next = w_ydalenie->next;
			delete w_ydalenie;
			p = first;
			return;
		}
		p = p->next;
		k++;
	}
	ERROR();
	p=first;
}

void ydalenie_vsego_spiska(m_list * &first) {
	while (first) {
		m_list *ydal = first;
		first = first->next;
		delete ydal;
	}
}

int kolichestvo_elementov(m_list * &first) {
	int S = 0;
	m_list *p = first;
	while (p) {
		p = p->next;
		S++;
	}
	return S;
}

int poisk_i_elementa(int nomer_iskomogo_elementa, m_list * &first) {
	int S = kolichestvo_elementov(first);
	int ii_element = 1;

	m_list *i_element = first;
	if (S < nomer_iskomogo_elementa || nomer_iskomogo_elementa<=0) {
		ERROR();
		return -1;
	}
	while (i_element) {
		if (ii_element == nomer_iskomogo_elementa) {
			return (i_element->inf);
		}
		i_element = i_element->next;
		ii_element++;
	}
}

m_list poisk_po_znacheniu(m_list * &first, m_list * &FIRST, int znachenie) {
	m_list *p = first;
	m_list *P = FIRST;
	m_list *W = P;
	int N = 1;
	while (p) {
		if (p->inf == znachenie) {
			P->inf = N;
			P->next = new m_list;
			W = P;
			P = P->next;
		}
		p = p->next;
		N++;
	}
	W->next = 0;
	return *FIRST;
}

void kopirovanie_spiska(m_list * &first, m_list * &pp) {
	if (first == 0) {
		ERROR();
		return;
	}
	m_list *p = first;
	pp->inf = p->inf;
	p = p->next;
	m_list * NEW_first = pp;
	while (p) {
		pp->next = new m_list;
		pp = pp->next;
		pp->inf = p->inf;
		p = p->next;
	}
	pp->next = 0;
	p = first;
}

void razbienie_spiska(m_list * &first, m_list * &chet_f, m_list * &nechet_f) {
	m_list *p = first;
	m_list *p_1 = chet_f;
	m_list *p_2 = nechet_f;
	m_list *w_1 = p_1;
	m_list *w_2 = p_2;
	while (p) {
		if (p->inf % 2) {
			p_2->inf = p->inf;
			p_2->next = new m_list;
			w_2 = p_2;
			p_2 = p_2->next;
		}
		else {
			p_1->inf = p->inf;
			p_1->next = new m_list;
			w_1 = p_1;
			p_1 = p_1->next;
		}
		p = p->next;
	}
	w_1->next = 0;
	w_2->next = 0;
}

void sortirovka(m_list * &first) {
	m_list *p = first;
	m_list *w = first->next;
	while (p) {
		while (w) {
			if (w->inf < p->inf) {
				int glass = p->inf;
				p->inf = w->inf;
				w->inf = glass;
			}
			w = w->next;
		}
		p = p->next;
		w = p;
	}
}

void interfeis (m_list * &first) {
	int n_elementov;//kol-vo elementov
	int num = 1;
	int k_posle_i = 0;
	int k_pered_i = 0;
	int k_ydalenie = 0;
	int nomer_iskomogo_elementa = 0;
	int znachenie = 0;
	while (num) {
		cout << "deistvie ";
		cin >> num;
		switch (num) {
			case 0: break;
			case 1:  {
				cout << "vvedite kolichestvo elementov: ";
				cin >> n_elementov;
				zapolnenie(n_elementov,first);
				break;
			}
			case 2:  {
				pechat(first);
				break;
			}
			case 3: {
				m_list *w_posle_i = new m_list;
				cout << "vvedite znachenie novogo elementa ";
				cin >> w_posle_i->inf;
				vstvka_v_nachalo(first, w_posle_i);
				break;
			}
			case 4: {
				m_list *w_pered_i = new m_list;
				cout << "vvedite znachenie novogo elementa ";
				cin >> w_pered_i->inf;
				vstavka_v_konec(first, w_pered_i);
				break;
			}
			case 5: {
				m_list *w_posle_i = new m_list;
				cout << "vvedite znachenie novogo elementa ";
				cin >> w_posle_i->inf;
				cout << "posle kakogo elementa stavit` ";
				cin >> k_posle_i;
				vstavka_posle_i(k_posle_i, first, w_posle_i);
				break;
			}
			case 6: {
				m_list *w_pered_i = new m_list;
				cout << "vvedite znachenie novogo elementa ";
				cin >> w_pered_i->inf;
				cout << "pered kakim elementom stavit` ";
				cin >> k_pered_i;
				vstavka_pered_i(k_pered_i, first, w_pered_i);
				break;
			}
			case 7: {
				
				cout << "kakoi element ydalit` ";
				cin >> k_ydalenie;
				ydalenie_i_elementa(k_ydalenie, first);
				break;
			}
			case 8: {
				ydalenie_vsego_spiska(first);
				break;
			}
			case 9: {
				cout << "V spiske " << kolichestvo_elementov(first) << " element(ov)" << endl;
				break;
			}
			case 10: {
				cout << "vvedite nomer elementa ";
				cin >> nomer_iskomogo_elementa;
				cout << "znachenie elementa: " << poisk_i_elementa(nomer_iskomogo_elementa, first) << endl;
				break;
			}
			case 11: {
				m_list * FIRST = new m_list;
				cout << "nomer yzla: ";
				cin >> znachenie;
				cout << "nomer(a) vveden elementa: "<<endl;
				poisk_po_znacheniu(first, FIRST, znachenie);
				cout << "---------" << endl;
				pechat(FIRST);
				cout << "---------" << endl;
				ydalenie_vsego_spiska(FIRST);
				break;
			}
			case 12: {
				m_list *pp = new m_list;
				m_list * NEW_first = pp;
				cout << "novii list" << endl;
				kopirovanie_spiska(first,pp);
				pechat(NEW_first);
				break;
			}
			case 13: {
				m_list *chet_f = new m_list;
				m_list *nechet_f = new m_list;
				razbienie_spiska(first, chet_f, nechet_f);
				cout << "spisok chetnih" << endl;
				pechat(chet_f);
				cout << "spisok nechetnih" << endl;
				pechat(nechet_f);
				break;
			}
			case 14: {
				sortirovka(first);
				break;
			}
			case 70: {
				m_list *w_ydalenie;
				ydalenie_pervogo_elementa(first, w_ydalenie);
				break;
			}
			case 60: {
				m_list *w_ydalenie;
				ydalenie_poslednego_elementa(first, w_ydalenie);
				break;
			}
			default: ERROR();
		}
	}
}

int main()
{
	cout << "1 - sozdanie spiska" << endl;
	cout << "2 - pechat" << endl; 
	cout << "3 - vstsvka v nschalo" << endl; 
	cout << "4 - vstsvka v konec" << endl; 
	cout << "5 - vstsvka posle i" << endl; 
	cout << "6 - vstsvka peredi" << endl; 
	cout << "7 - ydalenie i elementa" << endl; 
	cout << "8 - ydalenie spiska" << endl; 
	cout << "9 - kolichestvo elementov" << endl; 
	cout << "10 - poisk po nomery" << endl;
	cout << "11 - poisk po znacheniu" << endl;
	cout << "12 - kopirovanie spiska" << endl;
	cout << "13 - razbienie spiska" << endl;
	cout << "14 - sortirovka" << endl;
	
	m_list *first = 0;
	interfeis(first);

	
	return 0;
}
