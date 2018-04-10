// ***************************
// Date:
// Author:
// Module Name: Registers
// Description:
// ***************************
/* verilator lint_off WIDTH */
/* verilator lint_off UNUSED */

module Registers #(parameter WIDTH = 32) (
    input logic               i_clk,
    input logic               i_reset,
    input logic               i_regwrite,
    input logic               i_memtoreg,
    input logic [4:0]         i_RegA_addr,
    input logic [4:0]         i_RegB_addr,
    input logic [4:0]         i_RegD_addr,
    input logic  [WIDTH-1:0]  i_Memdata,
    input logic  [WIDTH-1:0]  i_ALUout,
    output logic [WIDTH-1:0]    o_RegA,
    output logic [WIDTH-1:0]    o_RegB);

// INTERNAL VARIABLES ********

    logic [WIDTH-1:0] RegTable [7:0];
    logic [WIDTH-1:0]    Data;

// MODULE START***************

assign RegTable[0] = 'b0;


always_ff @(posedge i_clk) begin : proc_Data
    Data <= i_Memdata;
end


always_ff @(posedge i_clk) begin
    // if(i_reset)
    //     RegTable[i_RegD_addr] <= 0;
    if (i_regwrite) begin
        if (i_memtoreg)
            RegTable[i_RegD_addr] <= Data;
        else
            RegTable[i_RegD_addr] <= i_ALUout;
    end
end

always_ff @(posedge i_clk) begin
    // if(i_reset) begin
    //     // Reset State
    //     o_RegA <= 'b0;
    //     o_RegB <= 'b0;
    // end
    // else begin
        o_RegA <= 'b0;
        o_RegB <= 'b0;
        if (|i_RegA_addr[2:0])
            o_RegA <= RegTable[i_RegA_addr];
        if (|i_RegB_addr[2:0])
            o_RegB <= RegTable[i_RegB_addr];
    end
endmodule // Registers