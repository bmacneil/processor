// ***************************
// Date:
// Author:
// Module Name: InstrDecoder
// Description:
// ***************************
// verilator lint_off UNUSED
module InstrDecoder #(parameter WIDTH = 32) (
    input logic                i_clk,
    input logic                i_reset,
    input logic                i_instrwrite,
    input logic                i_regdst,
    input logic  [WIDTH-1:0]   i_Memdata,
    output logic [4:0]         o_RegA_addr,
    output logic [4:0]         o_RegB_addr,
    output logic [4:0]         o_RegD_addr,
    output logic [5:0]         o_op,
    output logic [5:0]         o_funct,
    output logic [WIDTH-1:0]   o_Imm);

// INTERNAL VARIABLES ********
logic  [WIDTH-1:0] instruction;

// MODULE START***************


always_ff @(posedge i_clk) begin
    // if(i_reset) begin
    //     // Reset State
    //     instruction <= 'b0;
    // end
    // else begin
        if(i_instrwrite) begin
            instruction <= i_Memdata;
    end
end

assign o_RegA_addr = instruction[25:21];
assign o_RegB_addr = instruction[20:16];
assign o_RegD_addr = i_regdst ? instruction[15:11] : instruction[20:16];
assign o_op = instruction[WIDTH-1:WIDTH-6];
assign o_funct = instruction[5:0];
assign o_Imm = {16'b0, instruction[15:0]};

endmodule // InstrDecoder