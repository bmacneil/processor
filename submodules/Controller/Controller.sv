// ***************************
// Date:
// Author:
// Module Name: Controller
// Description:
// ***************************
`include "submodules/ALUDec/ALUDec.sv"
`include "submodules/StateMachine/StateMachine.sv"

module Controller(
    input logic         i_clk,
    input logic         i_reset,
    input logic         i_zero,
    input logic [5:0]   i_funct,
    input logic [5:0]   i_op,
    // output logic        o_memread,
    output logic        o_memwrite,
    output logic        o_alusrca,
    output logic        o_memtoreg,
    output logic        o_instrwrite,
    output logic        o_pcen,
    output logic        o_regwrite,
    output logic        o_regdst,
    output logic        o_iord,
    output logic [1:0]  o_pcsrc,
    output logic [1:0]  o_alusrcb,
    output logic [2:0]  o_alucontrol);

// INTERNAL SIGNALS ********
    logic [1:0]     aluop;
    logic           branch;
    logic           pcwrite;

// SUB MODULES ***************
ALUDec aludec(
    .i_aluop        ( aluop ),  // Size [1, 0]
    .i_funct        ( i_funct ),  // Size [5, 0]
    .o_alucontrol   ( o_alucontrol )  // Size [2, 0]
    );

// ******************************
StateMachine fsm(
    .i_clk          ( i_clk ),  // Size []
    .i_reset        ( i_reset ),  // Size []
    .i_op           ( i_op ),  // Size [5, 0]
    // .o_memread      ( o_memread ),  // Size []
    .o_memwrite     ( o_memwrite ),  // Size []
    .o_alusrca      ( o_alusrca ),  // Size []
    .o_memtoreg     ( o_memtoreg ),  // Size []
    .o_instrwrite   ( o_instrwrite ),  // Size []
    .o_iord         ( o_iord ),  // Size []
    .o_pcwrite      ( pcwrite ),  // Size []
    .o_regwrite     ( o_regwrite ),  // Size []
    .o_regdst       ( o_regdst ),  // Size []
    .o_branch       ( branch ),  // Size []
    .o_pcsrc        ( o_pcsrc ),  // Size [1, 0]
    .o_alusrcb      ( o_alusrcb ),  // Size [1, 0]
    .o_aluop        ( aluop )  // Size [1, 0]
    );

// MODULE START***************
assign o_pcen = pcwrite | (i_zero & branch);

endmodule // Controller