// ***************************
// Date:
// Author:
// Module Name: Datapath
// Description:
// ***************************
`include "submodules/Registers/Registers.sv"
`include "submodules/InstrDecoder/InstrDecoder.sv"
`include "submodules/PCdec/PCdec.sv"
`include "submodules/ALUmux/ALUmux.sv"
`include "submodules/ALU/ALU.sv"

module Datapath #(parameter WIDTH = 32) (
    input logic              i_clk,
    input logic              i_reset,
    // Inputs from Controller
    input logic              i_regwrite,
    input logic              i_memtoreg,
    input logic              i_regdst,
    input logic              i_instrwrite,
    input logic              i_PCen,
    input logic              i_IorD,
    input logic              i_AluSrcA,
    input logic  [1:0]       i_PCsrc,
    input logic  [1:0]       i_AluSrcB,
    input logic  [2:0]       i_alucontrol,
    output logic [5:0]       o_op,
    output logic [5:0]       o_funct,
    output logic             o_zero,
    //External Inputs
    input logic  [WIDTH-1:0] i_Memdata,
    output logic [WIDTH-1:0] o_WriteData,
    output logic [WIDTH-1:0] o_Address);

// INTERNAL VARIABLES ********
/* verilator lint_off UNDRIVEN */
    logic [4:0]        RegA_addr;
    logic [4:0]        RegB_addr;
    logic [4:0]        RegD_addr;
    logic [WIDTH-1:0]  RegA;
    logic [WIDTH-1:0]  RegB;
    logic [WIDTH-1:0]  AluA;
    logic [WIDTH-1:0]  AluB;
    logic [WIDTH-1:0]  ALUresult;
    logic [WIDTH-1:0]  Imm;
    logic [WIDTH-1:0]  ALUout;
    logic [WIDTH-1:0]  PC;

// SUB MODULES *******************
Registers registers(
    .i_clk          ( i_clk ),  // Size []
    .i_reset        ( i_reset ),  // Size []
    .i_regwrite     ( i_regwrite ),  // Size []
    .i_memtoreg     ( i_memtoreg ),  // Size []
    .i_RegA_addr    ( RegA_addr ),  // Size [4, 0]
    .i_RegB_addr    ( RegB_addr ),  // Size [4, 0]
    .i_RegD_addr    ( RegD_addr ),  // Size [4, 0]
    .i_Memdata      ( i_Memdata ),  // Size [31, 0]
    .i_ALUout       ( ALUout ),  // Size [31, 0]
    .o_RegA         ( RegA ),  // Size [31, 0]
    .o_RegB         ( RegB )  // Size [31, 0]
);

// ******************************
InstrDecoder instr_decoder(
    .i_clk          ( i_clk ),  // Size []
    .i_reset        ( i_reset ),  // Size []
    .i_instrwrite   ( i_instrwrite ),  // Size []
    .i_regdst       ( i_regdst ),  // Size []
    .i_Memdata      ( i_Memdata ),  // Size [31, 0]
    .o_RegA_addr    ( RegA_addr ),  // Size [4, 0]
    .o_RegB_addr    ( RegB_addr ),  // Size [4, 0]
    .o_RegD_addr    ( RegD_addr ),  // Size [4, 0]
    .o_Imm          ( Imm ),  // Size [31, 0]
    .o_op           ( o_op ),  // Size [5, 0]
    .o_funct        ( o_funct )  // Size [5, 0]
);

// ******************************
PCdec pc_decoder(
    .i_clk          ( i_clk ),  // Size []
    .i_reset        ( i_reset ),  // Size []
    .i_PCen         ( i_PCen ),  // Size []
    .i_IorD         ( i_IorD ),  // Size []
    .i_PCsrc        ( i_PCsrc ),  // Size [1, 0]
    .i_ALUresult    ( ALUresult ),  // Size [31, 0]
    .i_Imm          ( Imm ),  // Size [31, 0]
    .o_ALUout       ( ALUout ),  // Size [31, 0]
    .o_PC           ( PC ),  // Size [31, 0]
    .o_Address      ( o_Address )  // Size [31, 0]
);

// ******************************
ALU alu(
    .i_a            ( AluA ),  // Size [31, 0]
    .i_b            ( AluB ),  // Size [31, 0]
    .i_alucontrol   ( i_alucontrol ),  // Size [2, 0]
    .o_result       ( ALUresult ),  // Size [31, 0]
    .o_zero         ( o_zero )  // Size []
);

// ******************************
ALUmux alu_mux(
    .i_AluSrcA      ( i_AluSrcA ),  // Size []
    .i_AluSrcB      ( i_AluSrcB ),  // Size [1, 0]
    .i_PC           ( PC ),  // Size [31, 0]
    .i_RegA         ( RegA ),  // Size [31, 0]
    .i_RegB         ( RegB ),  // Size [31, 0]
    .i_Imm          ( Imm ),  // Size [31, 0]
    .o_AluA         ( AluA ),  // Size [31, 0]
    .o_AluB         ( AluB )  // Size [31, 0]
);
// MODULE START***************

assign o_WriteData = RegB;

endmodule // Datapath