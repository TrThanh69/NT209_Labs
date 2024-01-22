.section .data
output:
	.string "Enter a number (1-digit): "
output_len = . -output
rg:
		.string "\n"
rg_len = .-rg
.section .bss
	.lcomm number1,2

.section .text
	.globl _start
_start:
	//Output: Nhập 1 số (có 1 chữ số)
	movl $output_len, %edx
	movl $output, %ecx
	movl $1, %ebx
	movl $4, %eax
	int $0x80

	//Input: Nhập 1 số
	movl $2, %edx
	movl $number1, %ecx
	movl $0, %ebx
	movl $3, %eax
	int $0x80
	//Quá trình tính toán
		//Chuyển ký tự số về decimal
		subl $48,number1

		//Đảo ngược bit để số chẵn bit cuối=1 số lẻ bit cuối=0
		notl number1

		//And với 1 để giữ lại bit cuối
		andl $1,number1

		//chuyển ngược lại từ decimal sang ký tự số
		addl $48,number1


	//Xuất kết quả
	movl $5, %edx
	movl $number1, %ecx
	movl $1, %ebx
	movl $4, %eax
	int $0x80
	
	//Hàng mới
	movl $rg_len, %edx
	movl $rg, %ecx
	movl $1, %ebx
	movl $4, %eax
	int $0x80

	//Thoát chương trình
	movl $1, %eax
	int $0x80



