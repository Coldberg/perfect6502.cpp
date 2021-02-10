﻿/*
 Copyright (c) 2010,2014,2020 Michael Steil, Brian Silverman, Barry Silverman, Aleksandr Ševčenko

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#include <memory>
#include <span>

struct netlist_6502
{
	enum bits
	{
		reg_a,
		reg_x,
		reg_y,
		reg_s,
		reg_p,
		reg_pc,
		reg_pcl,
		reg_pch,
		reg_ir,
		bus_addr,
		bus_data,
		bus_irq,
		bus_nmi,
		bus_reset,
		bus_rw,
		bus_sync,
		bus_ready,
		bus_clock
	};

	netlist_6502();
 ~netlist_6502();
	
	netlist_6502(const netlist_6502&) = delete;

	void eval();
	auto get (bits) const -> uint16_t;
	void set (bits, uint16_t);

private:

	std::unique_ptr<struct state_type> state;
};


