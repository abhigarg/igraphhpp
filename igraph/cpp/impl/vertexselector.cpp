/*

vertexselector.cpp ... Vertex selector wrapper implementation

Copyright (C) 2009  KennyTM~

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

#ifndef IGRAPH_VERTEXSELECTOR_CPP
#define IGRAPH_VERTEXSELECTOR_CPP

#include <igraph/cpp/vertexselector.hpp>
#include <igraph/cpp/graph.hpp>

namespace igraph {
	MEMORY_MANAGER_IMPLEMENTATION(VertexSelector);
	XXINTRNL_WRAPPER_CONSTRUCTOR_IMPLEMENTATION(VertexSelector, igraph_vs_t, igraph_vs_copy);
	
	IMPLEMENT_COPY_METHOD(VertexSelector) {
		TRY(igraph_vs_copy(&_, &other._));
		retained_vector = other.retained_vector;
	}
	
	IMPLEMENT_MOVE_METHOD(VertexSelector) {
		_ = ::std::move(other._);
		retained_vector = ::tempobj::force_move(other.retained_vector);
	}
	
	IMPLEMENT_DEALLOC_METHOD(VertexSelector) {
		igraph_vs_destroy(&_);
	}

	::tempobj::force_temporary_class<VertexSelector>::type VertexSelector::all() MAY_THROW_EXCEPTION {
		igraph_vs_t _ = igraph_vss_all();
		return ::tempobj::force_move(VertexSelector(&_, ::tempobj::OwnershipTransferNoOwnership));
	}
	
	::tempobj::force_temporary_class<VertexSelector>::type VertexSelector::adj(const Vertex which, const NeighboringMode mode) MAY_THROW_EXCEPTION {
		igraph_vs_t _;
		igraph_vs_adj(&_, which, (igraph_neimode_t)mode);
		return ::tempobj::force_move(VertexSelector(&_, ::tempobj::OwnershipTransferMove));
	}
	
	::tempobj::force_temporary_class<VertexSelector>::type VertexSelector::nonadj(const Vertex which, const NeighboringMode mode) MAY_THROW_EXCEPTION {
		igraph_vs_t _;
		TRY(igraph_vs_nonadj(&_, which, (igraph_neimode_t)mode));
		return ::tempobj::force_move(VertexSelector(&_, ::tempobj::OwnershipTransferMove));
	}
	
	::tempobj::force_temporary_class<VertexSelector>::type VertexSelector::none() MAY_THROW_EXCEPTION {
		igraph_vs_t _ = igraph_vss_none();
		return ::tempobj::force_move(VertexSelector(&_, ::tempobj::OwnershipTransferNoOwnership));
	}
	
	::tempobj::force_temporary_class<VertexSelector>::type VertexSelector::single(const Vertex which) MAY_THROW_EXCEPTION {
		igraph_vs_t _ = igraph_vss_1(which);
		return ::tempobj::force_move(VertexSelector(&_, ::tempobj::OwnershipTransferNoOwnership));
	}
	
	::tempobj::force_temporary_class<VertexSelector>::type VertexSelector::vector(const VertexVector& vec, const ::tempobj::OwnershipTransfer transfer) MAY_THROW_EXCEPTION {
		igraph_vs_t _;
		switch (transfer) {
			case ::tempobj::OwnershipTransferCopy: {
				TRY(igraph_vs_vector_copy(&_, &vec._));
				return ::tempobj::force_move(VertexSelector(&_, ::tempobj::OwnershipTransferMove));
			}
			case ::tempobj::OwnershipTransferMove: {
				_ = igraph_vss_vector(&vec._);
				VertexSelector vs = VertexSelector(&_, ::tempobj::OwnershipTransferNoOwnership);
				vs.retained_vector = ::tempobj::force_move(vec);
				return ::std::move(vs);
			}
			case ::tempobj::OwnershipTransferKeepOriginal: {
				_ = igraph_vss_vector(&vec._);
				return ::tempobj::force_move(VertexSelector(&_, ::tempobj::OwnershipTransferNoOwnership));
			}
		}
		std::unexpected();
	}
	
	::tempobj::force_temporary_class<VertexSelector>::type VertexSelector::seq(const Vertex fromID, const Vertex toID) MAY_THROW_EXCEPTION {
		igraph_vs_t _ = igraph_vss_seq(fromID, toID);
		return ::tempobj::force_move(VertexSelector(&_, ::tempobj::OwnershipTransferNoOwnership));
	}
	
	int VertexSelector::type() const throw() { return igraph_vs_type(&_); }
	bool VertexSelector::is_all() MAY_THROW_EXCEPTION { return igraph_vs_is_all(&_); }

	::tempobj::force_temporary_class<VertexVector>::type VertexSelector::as_vector(const Graph& g) const MAY_THROW_EXCEPTION {
		igraph_vector_t res;
		igraph_vector_init(&res, 0);
		TRY(igraph_vs_as_vector(&g._, _, &res));
		return ::tempobj::force_move(VertexVector(&res, ::tempobj::OwnershipTransferMove));
	}
	
	Integer VertexSelector::size(const Graph& g) const MAY_THROW_EXCEPTION {
		Integer s = 0;
		TRY(igraph_vs_size(&g._, &_, &s));
		return s;
	}
	
}

#endif
