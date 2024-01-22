.section .data
output:
	.string "Nhap 1 chu cai: \n"
output_len = . -output

rgu:
		.string "CHU IN HOA\n"
rgu_len = .-rgu

rgl:
		.string "chu in thuong\n"
rgl_len = .-rgl

rgn:
		.string "Khong phai ky tu\n"
rgn_len = .-rgn

.section .bss
	.lcomm word1,2

.section .text
	.globl _start

_start:
	//Output: Nhập 1 ký tự
	movl $output_len, %edx
	movl $output, %ecx
	movl $1, %ebx
	movl $4, %eax
	int $0x80

	//Input: Nhập 1 ký tự
	movl $2, %edx
	movl $word1, %ecx
	movl $0, %ebx
	movl $3, %eax
	int $0x80

	//Quá trình tính toán
		//lấy 1 byte tương ứng với ký tự đã nhập
        mov (word1) ,%cl

        //So sánh các khoảng A đến Z (cả chữ in thường)
            //So sánh chữ in HOA (>= 65)
            cmpb $65, %cl
            jge _la_chu_HOA

            //Nếu không thuộc khoản HOA hay thường
            _ky_tu_khac:
            movl $rgn, %ecx
            movl $rgn_len, %edx
            jmp _exit

            //So sánh chữ in HOA (<= 91)
            _la_chu_HOA:
            cmpb $91, %cl
            jge _la_chu_thuong
            movl $rgu, %ecx
            movl $rgu_len, %edx
            jmp _exit

            //So sánh chữ in thường (>= 97)
            _la_chu_thuong:
            cmpb $97, %cl
            jl _ky_tu_khac
            //So sánh chữ in thường (<= 122)
            cmpb $122, %cl
            jg _ky_tu_khac
            movl $rgl, %ecx
            movl $rgl_len, %edx
	  
	//In kết quả 
    _exit:
    movl $4, %eax
    movl $1, %ebx
    int $0x80

    //Thoát chương trình
	movl $1, %eax
	int $0x80


