// ***************************
// Date:
// Author:
// Module Name: ALUmux
// Description:
// ***************************

module ALUmux #  ( parameter WIDTH = 32) (
    input logic                 i_AluSrcA,
    input logic  [1:0]          i_AluSrcB,
    input logic  [WIDTH-1:0]    i_PC,
    input logic  [WIDTH-1:0]    i_RegA,
    input logic  [WIDTH-1:0]    i_RegB,
    input logic  [WIDTH-1:0]    i_Imm,
    output logic [WIDTH-1:0]    o_AluA,
    output logic [WIDTH-1:0]    o_AluB);

// INTERNAL VARIABLES ********
logic [WIDTH-1:0] imm_shift;

// MODULE START***************
assign imm_shift = i_Imm;

always_comb begin
    /* verilator lint_off WIDTH */
    case(i_AluSrcA)
        1'b0 : o_AluA = i_PC;
        1'b1 : o_AluA = i_RegA;
    endcase // i_AluSrcA

    case(i_AluSrcB)
        2'b00 : o_AluB = i_RegB;
        2'b01 : o_AluB = 'b1;
        2'b10 : o_AluB = i_Imm;
        2'b11 : o_AluB = imm_shift;
    endcase // i_AluSrcB
end

endmodule // ALUmux