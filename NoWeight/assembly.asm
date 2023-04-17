extern noWeightBack:QWORD

.code
noWeightAsm_func proc
	xorps xmm6, xmm6
	inc ebx
	cmp ebx, 05
	jmp noWeightBack
noWeightAsm_func endp
end