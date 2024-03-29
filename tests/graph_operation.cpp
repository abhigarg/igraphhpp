/*

graph_operation.cpp ... Tests all graph opertions including disjoint union, merge, intersection...

Copyright (C) 2009  Hon Wai, LAU <lau65536@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <igraph/igraph.hpp>
#include <cstdio>
using namespace std;
using namespace igraph;

int main () {
	Graph F = Graph::ring(6);
	Graph G = Graph::lattice_2d(2,3);
	Graph H = Graph::star(6);
	Graph J = Graph::full(6);

	printf("\n\nGraph operation fucntion test\n----------------\n");	
	Graph::disjoint_union(F,H).writer(stdout).adjlist();  printf("\n---\n");
	Graph::merge(F,H).writer(stdout).adjlist();  printf("\n---\n");
	Graph::intersection(F,H).writer(stdout).adjlist();  printf("\n---\n");
	Graph::difference(F,H).writer(stdout).adjlist();  printf("\n---\n");
	Graph::complementer(H).writer(stdout).adjlist();  printf("\n---\n");
	Graph::compose(F,H).writer(stdout).adjlist();  printf("\n---\n");
	Graph::multiply(F,3).writer(stdout).adjlist();  printf("\n---\n");

	printf("\n\nGraph operator test\n----------------\n");
	(F + H).writer(stdout).adjlist();  printf("\n---\n");
	(F | H).writer(stdout).adjlist();  printf("\n---\n");
	(F & H).writer(stdout).adjlist();  printf("\n---\n");
	(F - H).writer(stdout).adjlist();  printf("\n---\n");
	(~H).writer(stdout).adjlist();  printf("\n---\n");

	printf("\n\nGraph operators combination test\n----------------\n");
	Graph t1 = (~H) - F;
	t1.writer(stdout).adjlist();  printf("\n---\n");
	Graph t2 = (J - G) | H;
	t2.writer(stdout).adjlist();  printf("\n---\n");
	Graph t3 = (J - G) + (F & H);
	t3.writer(stdout).adjlist();  printf("\n---\n");

	printf("\n\ngraph operation : decompose\n----------------\n");
	ReferenceVector<Graph> glist = (F + G + H).decompose();
	for(long i=0; i<glist.size(); ++i) {
		glist[i].writer(stdout).adjlist();  printf("\n---\n");
	}

	printf("\n\ngraph operation many\n----------------\n");
	glist.push_back(J);
	Graph::disjoint_union(glist).writer(stdout).adjlist();  printf("\n---\n");
	Graph::merge(glist).writer(stdout).adjlist();  printf("\n---\n");
	Graph::intersection(glist).writer(stdout).adjlist();  printf("\n---\n");

	printf("\n\nTest end\n----------------\n");

	return 0;
}
