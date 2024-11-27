__attribute__((naked)) void call_svc();

int main (){
	
	call_svc();
	// see how can i return to the assembler via the link register
	// i have to save the old LR before calling call_svc maybe
	__asm("BX LR\n");
}