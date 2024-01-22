.section .data
output:
	.string "Nhap 1 so nguyen co 3 chu so: \n"
output_len = . -output

rgy:
		.string "Tang dan\n"
rgy_len = .-rgy

rgn:
		.string "Khong tang dan\n"
rgn_len = .-rgn


.section .bss
	.lcomm number,3

.section .text
	.globl _start

_start:
	//Output: Nhập 1 số nguyên 
	movl $output_len, %edx
	movl $output, %ecx
	movl $1, %ebx
	movl $4, %eax
	int $0x80

	//Input: Nhập 1 số nguyên 
	movl $4, %edx
	movl $number, %ecx
	movl $0, %ebx
	movl $3, %eax
	int $0x80

    //Tách các chữ số 
    movl $number,%eax
    mov (%eax),%cl
    mov 1(%eax),%ch
    mov 2(%eax),%bl
    
	//Quá trình tính toán
		//So sánh 3 chữ số

        //So sánh số 1 và số 2
        cmpb %cl,%ch 
        jg _Tang_dan

        cmpb %cl,%ch 
        je _neu_bang_nhau

        //Nếu số 2 bé hơn 1 hoặc số 3 bé hơn 2
        _Khong_tang_dan:
        movl $rgn, %ecx
        movl $rgn_len, %edx
        jmp _exit

        //So sánh số 2 và số 3
        _Tang_dan:
        cmpb %ch,%bl
        jl _Khong_tang_dan
        movl $rgy, %ecx
        movl $rgy_len, %edx
        jmp _exit

        _neu_bang_nhau:
        cmpb %ch,%bl
        jle _Khong_tang_dan
        movl $rgy, %ecx
        movl $rgy_len, %edx
        jmp _exit

	//In kết quả 
    _exit:
    movl $4, %eax
    movl $1, %ebx
    int $0x80

    //Thoát chương trình
	movl $1, %eax
	int $0x80
