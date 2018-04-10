// ***************************
// Date:
// Author:
// Module Name: ALUDec
// Description:
// ***************************

module ALUDec(
        input  logic [1:0] i_aluop,
        input  logic [5:0] i_funct,
        output logic [2:0] o_alucontrol);

// INTERNAL VARIABLES ********
typedef enum logic [5:0] {ADD = 6'b100000,
                          SUB = 6'b100010,
                          AND = 6'b100100,
                          OR  = 6'b100101,
                          SLT = 6'b101010} functcode;

// MODULE START***************
always_comb
    case (i_aluop)
        2'b01 : o_alucontrol = 3'b110;
        2'b00 : o_alucontrol = 3'b010;
        default : case (i_funct)
            ADD : o_alucontrol = 3'b010;
            SUB : o_alucontrol = 3'b110;
            AND : o_alucontrol = 3'b001;
            OR  : o_alucontrol = 3'b000;
            SLT : o_alucontrol = 3'b111;
            default : o_alucontrol = 3'b010;
        endcase
    endcase

endmodule // ALUDec