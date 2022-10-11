// NextStateģ���ʵ��
// @param i_state �����״̬
// @param opcode ����Ĳ�����
// @param next_state ��һ״̬
module NextState(i_state, opcode, next_state);
    input [2:0]i_state;
    input [5:0]opcode;
    output reg[2:0]next_state;
    parameter [2:0] IF = 3'b000, // IF״̬
                     ID = 3'b001, // ID״̬
                     aEXE = 3'b110, // ��һ����֧��EXE״̬
                     bEXE = 3'b101, // �ڶ�����֧��EXE״̬
                     cEXE = 3'b010, // ��������֧��EXE״̬
                     MEM = 3'b011, // MEM״̬
                     aWB = 3'b111, // ��һ����֧��WB״̬
                     cWB = 3'b100; // ��������֧��WB״̬
    always @(i_state or opcode) begin
        case (i_state)
            IF: next_state = ID;
            ID: begin
                case (opcode[5:3])
                    3'b110: begin
                        if (opcode == 6'b110100) next_state = bEXE; // beqָ��
                        else next_state = cEXE; // sw, lwָ��
                    end
                    3'b111: next_state = IF; // j, jal, jr, haltָ��
                    default: next_state = aEXE; // add, sub��ָ��
                endcase
            end
            aEXE: next_state = aWB;
            bEXE: next_state = IF;
            cEXE: next_state = MEM;
            MEM: begin
                if (opcode == 6'b110001) next_state = cWB; // lwָ��
                else next_state = IF; // swָ��
            end
            aWB: next_state = IF;
            cWB: next_state = IF;
            default: next_state = IF;
        endcase
    end
endmodule