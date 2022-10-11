// �������ģ���ʵ��
// @param state ��ǰ״̬
// @param opcode ������
// @param PCWre PC�Ŀ����ź�
// @param InsMemRW ָ��洢���Ŀ����ź�
// @param IRWre IR�Ŀ����ź�
// @param WrRegData ���ƼĴ�����д���ݶ˿ڵ�����ѡ����
// @param RegWre �Ĵ�����Ŀ����ź�
// @param ALUSrcA ����ALU��A����˿ڵ�����ѡ����
// @param ALUSrcB ����ALU��B����˿ڵ�����ѡ����
// @param DataMemRW ���ݴ洢���Ŀ����ź�
// @param DBDataSrc �������ݴ洢������˿ڵ�����ѡ����
// @param ExtSel ������չ��Ԫ�Ŀ����ź�
// @param RegDst ���ƼĴ�����д�Ĵ����˿ڵ�����ѡ����
// @param PCSrc ��ѡһѡ�����Ŀ����ź�
// @param ALUOp ALU�Ŀ����ź�
module OutputFunc(state, opcode, zero, PCWre, InsMemRW, IRWre, WrRegData, RegWre, ALUSrcA, ALUSrcB, DataMemRW, DBDataSrc, ExtSel, RegDst, PCSrc, ALUOp);
    input [2:0]state;
    input [5:0]opcode;
    input zero;
    output reg PCWre, InsMemRW, IRWre, WrRegData, RegWre, ALUSrcA, ALUSrcB, DataMemRW, DBDataSrc;
    output reg[1:0]ExtSel, RegDst, PCSrc;
    output reg[2:0]ALUOp;
    parameter [2:0] IF = 3'b000, // IF״̬
                     ID = 3'b001, // ID״̬
                     aEXE = 3'b110, // ��һ֧·��EXE״̬
                     bEXE = 3'b101, // �ڶ�֧·��EXE״̬
                     cEXE = 3'b010, // ����֧·��EXE״̬
                     MEM = 3'b011, // MEM״̬
                     aWB = 3'b111, // ��һ֧·��WB״̬
                     cWB = 3'b100; // ����֧·��WB״̬
    parameter [5:0] addi = 6'b000010,
                     ori = 6'b010010,
                     sll = 6'b011000,
                     add = 6'b000000,
                     sub = 6'b000001,
                     slt = 6'b100110,
                     slti = 6'b100111,
                     sw = 6'b110000,
                     lw = 6'b110001,
                     beq = 6'b110100,
                     j = 6'b111000,
                     jr = 6'b111001,
                     Or = 6'b010000,
                     And = 6'b010001,
                     jal = 6'b111010,
                     halt = 6'b111111;

    always @(state) begin
        // ��PCWre��ֵ
        if (state == IF && opcode != halt) PCWre = 1;
        else PCWre = 0;
        // ��InsMemRW��ֵ
        InsMemRW = 1;
        // ��IRWre��ֵ
        if (state == IF) IRWre = 1;
        else IRWre = 0;
        // ��WrRegData��ֵ
        if (state == aWB || state == cWB) WrRegData = 1;
        else WrRegData = 0;
        // ��RegWre��ֵ
        if (state == aWB || state == cWB || opcode == jal) RegWre = 1;
        else RegWre = 0;
        // ��ALUSrcA��ֵ
        if (opcode == sll) ALUSrcA = 1;
        else ALUSrcA = 0;
        // ��ALUSrcB��ֵ
        if (opcode == addi || opcode == ori || opcode == slti|| opcode == sw || opcode == lw) ALUSrcB = 1;
        else ALUSrcB = 0;
        // ��DataMemRW��ֵ
        if (state == MEM && opcode == sw) DataMemRW = 1;
        else DataMemRW = 0;
        // �� DBDataSrc��ֵ
        if (state == cWB) DBDataSrc = 1;
        else DBDataSrc = 0;
        // ��ExtSel��ֵ
        if (opcode == ori) ExtSel = 2'b01;
        else if (opcode == sll) ExtSel = 2'b00;
        else ExtSel = 2'b10;
        // ��RegDst��ֵ
        if (opcode == jal) RegDst = 2'b00;
        else if (opcode == addi || opcode == ori || opcode == lw) RegDst = 2'b01;
        else RegDst = 2'b10;
        // ��PCSrc��ֵ
        case(opcode)
            j: PCSrc = 2'b11;
            jal: PCSrc = 2'b11;
            jr: PCSrc = 2'b10;
            beq: begin
                if (zero) PCSrc = 2'b01;
                else PCSrc = 2'b00;
            end
            default: PCSrc = 2'b00;
        endcase
        // ��ALUOp��ֵ
        case(opcode)
            sub: ALUOp = 3'b001;
            Or: ALUOp = 3'b101;
            And: ALUOp = 3'b110;
            ori: ALUOp = 3'b101;
            slt: ALUOp = 3'b010;
            slti: ALUOp = 3'b010;
            sll: ALUOp = 3'b100;
            beq: ALUOp = 3'b001;
            default: ALUOp = 3'b000;
        endcase
        // ��ֹ��IF�׶�д����
        if (state == IF) begin
            RegWre = 0;
            DataMemRW = 0;
        end
    end

endmodule