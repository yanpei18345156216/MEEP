/* Copyright (C) 2003 Massachusetts Institute of Technology
%
%  This program is free software; you can redistribute it and/or modify
%  it under the terms of the GNU General Public License as published by
%  the Free Software Foundation; either version 2, or (at your option)
%  any later version.
%
%  This program is distributed in the hope that it will be useful,
%  but WITHOUT ANY WARRANTY; without even the implied warranty of
%  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%  GNU General Public License for more details.
%
%  You should have received a copy of the GNU General Public License
%  along with this program; if not, write to the Free Software Foundation,
%  Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include "meep.h"
#include "meep_internals.h"

namespace meep {

void fields::update_e_from_d() {
  for (int i=0;i<num_chunks;i++)
    if (chunks[i]->is_mine())
      chunks[i]->update_e_from_d();
}

void fields_chunk::update_e_from_d() {
  DOCMP FOR_ELECTRIC_COMPONENTS(ec)
    if (!d_minus_p[ec][cmp] &&
	((pol || e_sources) && f[ec][cmp]) || s->kerr[ec]) {
      d_minus_p[ec][cmp] = new double[v.ntot()];
      have_d_minus_p = true;
    }
  update_e_from_d_prepare();
  update_e_from_d_sources();
  update_e_from_d_update();
}

} // namespace meep
