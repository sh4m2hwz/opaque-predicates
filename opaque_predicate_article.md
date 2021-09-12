Доброго времени суток!
В этой статье я рассмотрю технику обфускации непрозрачные предикаты.

***Содержание***

1) Предисловие
2) Введение в opaque predicates
3) классификация opaque predicates
4) рассмотрение групп contextual opaque predicates по семантики потока исполнения.
5) рассмотрение смежных и не смежных opaque predicates
6) примеры и анализ
7) эпилог и заключение

***Конец Содержания***

***Предисловие***

Прежде чем начать что такое opaque predicates(непрозрачные предикаты),рассмотрим что такое обфускация.
Обфускация - это раздел криптографии, который изучает методы и принципы запутывание кода,усложнение его чтения и анализа как в статике так и в динамике.

Обфускация имеет 5 ветвей или подразделов изучающих обфусцирование семантики:
1) obfuscation binary semantic 
2) obfuscation control flow semantic
3) obfuscation data flow semantic
4) obfuscation format file semantic
# obfuscation <type> semantic - это запутывание и усложнение реализации программного кода,где семантически обфусцированная реализация и реализация до обфускации эквивалентны.
Я рассмотрю в этой статье 2 пункт "непрозрачные предикаты".

***Введение в opaque predicate***

Прежде чем рассмотрить ,что такое opaque predicate ,нужно понять ,что такое predicate(предикат).
Предикат или прозрачный предикат - это выражение имеющее булевую семантику,то есть результатом выражения всегда является булевое значение (true/false).
 Семантика предиката прозрачного понятна на этапе простого анализа или не требует анализа предиката(проще говоря каждый человек обладающий навыками программирования и отладки сможет понять без дополнительных техник что делает этот предикат),так как поведение предиката является явным и не требует тчательного анализа в отличие от opaque predicate.
Рассмотрим opaque predicate.
opaque predicate (непрозрачный предикат) - это предикат семантика которого является не тривиальной и сложной или даже не возможной при статическом анализе и затрудняющем сильно динамический анализ,поведение непрозрачного предиката известна только создателю непрозрачного предиката.
opaque predicate - это самый сложный вид обфускации потока исполнения при разработке и при анализе и оценки семантики обфусцированной программы.

***Классификация opaque predicate***

opaque predicate имеет свою классификацию и делится на типы:
1) Invariant opaque predicate
2) Contextual opaque predicate
3) dynamic opaque predicate

Рассмотрим первый тип opaque predicate.
Invariant opaque predicate - (Invariant переводится как без вариантов ,этот термин взят из математики,он означает что: переменная имеющая какое-то значение до операций ,будет иметь исходное(значение до операции) значение после математических операций ) это непрозрачный предикат,который либо всегда при любом условии или аргументов в логическом выражение возращает true или всегда false.
пример:
x*x+1<0 это выражение всегда будет возращать ложь,при условие что x принадлежит множеству целых,рациональных и иррациональных чисел,потому что при любом x, правая часть неравенства будет больше нуля и положительно.
Рассмотрим второй тип.
Contextual opaque predicate (Contextual или контекстный здесь показывает ,что непрозрачный предикат зависит от контекста(входных аргументов или параметров в предикат)) - это непрозрачный предикат который зависит от своего контекста ,а именно от аргументов,параметров,событий которые могут влиять на логическо выражение,на сам предикат ,этот тип не прозрачного предиката,в отличие от инвариантого непрозрачного предиката,может true или false возращать ,в зависимости от контекста ,который оказывает влияние на предикат.
Пример:
```
int func(int param1)
{
	if(-param1%2)
	{
		return 5;
	}
	else 
	{
		return 6;
	}
}
```
В этом примере выражение -param1%2 не всегда возращает true или false ,а в зависимости от значения param1,пример если param1=2 то условие возращает true,если param1=3,то условие возвращает false.

Рассмотрим 3 тип opaque predicate.
dynamic opaque predicate - это непрозрачный предикат выражение которого или аргументы являются динамическими,то есть только вовремя выполения понятна семантика предиката. Этот непрозрачный предикат может быть инвариантным динамическим непрозрачным предикатом или контекстным динамическим непрозрачным предикатом.
Это те же непрозрачные предикаты 1 и 2 типа,только величины или само выражение ,динамично.
Пример:
```
int func()
{
	int var;
	
	int fd = open("/dev/urandom",O_RDWR);
	read(fd,&var,4);
	
	if(var%2)
	{
		return 4;
	}
	else return -2;
}
```
в этом примере выражение в if ,оперирует с динамическими величинами и зависит от анешнего контекста а именно объекта модуля ядра при чтение которого мы получаем энтропию чисел безнаковых.Здесь поведение не возможно предсказать так как только понятно во воемя выполения.

***классы по семантике contextual opaque predicate***

contextual opaque predicate подразделяется на 2 типа по поведению семантики его блоков CFG.
1) эвристика блоков после этого типа предиката разная,но семантика идентична.
2) эвристика юлоков после этого типа предиката разная и семантика разная.

пример по первому типу:
```
int func(int param1,int param2)
{
	if((param1*cos(param2))%2)
	{
	return (param2<<3)^param1;
	}
	else
	{
		int i;
		for (i=1;i<3;i*2);
		param2*=i;
		return ((param1&param2) | ((~param1)&param2) | (param1&(~param2)));
	}
}
```
чтобы понять этот пример нужно вспомнить булеву алгебру,и представить xor как пару инверсий and и or'ов

пример по второму типу:
```
int func() 
{
	char *ptr=nullptr;
	if(check_in_vmbox())
	{
	*ptr; // call segmentation fault
	}
	else {
	// ... main code
	}
}
```
здесь я не стал все усложнять ,а представил ввиде простой абстракции враперов.
этот код работает так если мы под виртуалкой разименновываем нулевой указатель и программа крашается
иначе происходит нормальное исполнение кода ,врапером я здесь подразумеваю check_in_box() представьте ,что это inline function или макрос.

***рассмотрение смежных и не смежных opaque predicates***

непрозрачные предикат может состоять из несколько предикатов групп,которые взаимосвязанны это называется смежными предикатами
не смежные предикаты это наоборот ,когда непрозрачный предикат состоит из одного семантического булевого выражения.

пример:
```
int func(int param)
{
	int var = (~param|0x46445<<3)*13
	if (var%4 == 2)
	{
		if((param &0x55) >> 31)
		{
		return 3;
		}
	}
	else return 5;
}
```
В этом примере один предикат зависит от другого предиката если 1 if не сработает, 2 предикат не запуститься.

***примеры и анализ***

пример полноценного инварианта ,который всегда переходит на false ветку при заданом значение равном = 434:
https://godbolt.org/z/8Ghd83

код:
```
declare i32 @printf(i8*,i16,i16)
declare i32 @puts(i8*)
@string_vector = internal constant [36 x i8] c"vector<2 x i16>: <i16 %d>,<i16 %d>\0a\00"
@s_start_opaque_predicate = internal constant [34 x i8] c"start invariant opaque predicate\0a\00"
@block1 = internal constant [8 x i8] c"block1\0a\00"
@block2 = internal constant [8 x i8] c"block2\0a\00"
define void @print_v(<2 x i16> %v) 
{
	%el0 = extractelement <2 x i16> %v,i32 0
	%el1 = extractelement <2 x i16> %v,i32 1
	%string = bitcast [36 x i8]* @string_vector to i8*
	call i32 @printf(i8* %string,i16 %el0,i16 %el1)
	ret void
}

define i32 @main() 
{
entry:
; start nop instructions
    %l = alloca i32,align 4
    store i32 434,i32* %l,align 4
    %_0 = load i32,i32* %l,align 4
    %v_0 = bitcast i32 %_0 to <4 x i8>
    %v_1 = add <4 x i8> %v_0,<i8 -2,i8 -5,i8 4,i8 1>
    %v_2 = and <4 x i8> %v_1,%v_0
    %v_3 = udiv <4 x i8> %v_2,%v_1
    %v_4 = ashr <4 x i8> %v_3,<i8 2,i8 4,i8 4,i8 6>
    %r32 = bitcast <4 x i8> %v_4 to i32
    %d = load i32,i32* %l,align 4
    store i32 %r32,i32* %l,align 4
;end nop instructions
;start invariant opaque predicate + mutation
    %s1 = bitcast [34 x i8]* @s_start_opaque_predicate to i8*
    call i32 @puts(i8* %s1)
;x*(3-2*x)+x*13-456>0

    %t1 = or i32 -1,0
    %t2 = xor i32 %t1,4294967294 ; 1
    %t3 = shl i32 %t2,1 ; 2
    %t4 = mul i32 %t3,%d
    %t5 = sub i32 3,%t4
    %t6 = mul i32 %t5,%d
    %t7 = mul i32 2,6
    %t8 = bitcast i32 %t7 to <2 x i16>
    call void @print_v(<2 x i16> %t8)
    %t9 = bitcast i32 %t2 to <2 x i16>
    call void @print_v(<2 x i16> %t9)
    %el = extractelement <2 x i16> %t9,i32 0
    insertelement <2 x i16> %t9,i16 %el,i32 1
    %t10 = shufflevector <2 x i16> %t9,
    <2 x i16> %t8,<2 x i32> <i32 1,i32 2>
    %el1 = extractelement <2 x i16> %t10,i32 0
    %el2 = extractelement <2 x i16> %t10,i32 1
    %t11 = or i16 %el1,%el2
    %t12 = sext i16 %t11 to i32
    %t13 = mul i32 %t12,%d
    %t14 = add i32 %t13,%t6
    %t15 = sub i32 %t14,456
    %cond = icmp sgt i32 %t15,0
    ; end invariant opaque predicate
    br i1 %cond,label %b1,label %b2
b1:

; log start block1

    %s3 = bitcast [8 x i8]* @block1 to i8*
    call i32 @puts(i8* %s3)

;end log
    
; junk instructions

    %b1_1 = add i32 5,4
    %s = uitofp i32 %b1_1 to float
    %e = fneg float -424434.5
    %rr = frem float %s,%e
    %vl3 = fptrunc double 44343.4 to float
    fmul float %rr,%vl3
    %r1 = fptosi float %rr to i32
    br label %exit
b2:
; log  start block2
    %s4 = bitcast [8 x i8]* @block2 to i8*
    call i32 @puts(i8* %s4)
; end log

    ;some instructions
    %r2 = lshr i32 %t12,%t15
    br label %exit
exit:
    %r = phi i32 [%r1,%b1],[%r2,%b2]
    ret i32 %r
}
```
Анализ:

Я решил ввести логирование некоторых состояние программы ,для большего понимания состояние контекста.
В самом начале программы у меня есть функция print_v ,она просто печатает вектор.В начале main,я накидал мусорных инструкций для красоты,чтобы было похоже на настоящую обфускацию и дальше я отметил комментариями где начало и конец ,но это даже ясно из контекста, когда я вызываю puts на print "start invariant opaque predicate\0a\00"
после этого принта начинается самое интересное,статический непрозрачный предикат типа инвариантный,не смежный.

Рассмотрим более внимательно отрывок который  обозначил коментариями строка 37-61.
здесь я выполняю формулу которую я написал выше ,только добавив еще пермутации в код .
37 строка - 39 здесь я вычисляю значение 2.
40 строка - 42 здесь я выполняю левую часть выражения x*(3-2*x)+x*13-456,а именно x*(3-2*x).
строка 44 - 54 я вычисляю значение 13 через simd инструкции,выполняя технику обфускации развертывания констант.
строка 54 - 58 выполняю оставшиеся вычисления выражения ,а именно правую часть .
ну а дальше я получаю в строке 59 булевое значение и перехожу на блок b2 так как icmp вернуло false.

пример2:
```
declare i32 @open(i8*,i32)
declare i32 @read(i32,i64*,i32)
;declare i32 @printf(i8*,i32)
declare i32 @puts(i8*)
declare i32 @printf(i8*,i64,i64,i64,i64,i64)
@string1 = internal constant [13 x i8] c"/dev/urandom\00"
@debug1 = internal constant [9 x i8] c"in b1_2\0a\00"
@debug2 = internal constant [9 x i8] c"in b3_4\0a\00"
@debug3 = internal constant [12 x i8] c"in block%d\0a\00"
@debugr = internal constant [15 x i8] c"result: %lld \0a\00"
@debugargs = internal constant [39 x i8] c"result: a: %d\0ab: %d\0ac: %d\0ad: %d\0ae: %d\0a\00"

define void @pr_args([39 x i8]* %format,i64 %a,i64 %b,i64 %c,i64 %d,i64 %e) 
{
	%str = bitcast [39 x i8]* %format to i8*
	call i32 @printf(i8* %str,i64 %a,i64 %b,i64 %c,i64 %d,i64 %e)
	ret void
}

define void @pr_debug_result([15 x i8]* %info,i64 %r)
{
    %ptr = bitcast [15 x i8]* %info to i8*
    call i32 @printf(i8* %ptr,i64 %r,i64 0,i64 0,i64 0,i64 0)
    ret void
}

define void @pr_debug_blk([12 x i8]* %info,i64 %n) 
{
    %ptr = bitcast [12 x i8]* %info to i8*
    call i32 @printf(i8* %ptr,i64 %n,i64 0,i64 0,i64 0,i64 0)
    ret void
}


define void @pr_debug_blks([9 x i8]* %info) 
{
    %ptr = bitcast [9 x i8]* %info to i8*
    call i32 @puts(i8* %ptr)
    ret void
}

define i32 @main()
{
    %string1 = bitcast [13 x i8]* @string1 to i8*
    %fd = call i32 @open(i8* %string1,i32 2)
    %vars = alloca i64,i16 5,align 8
    %vars_predict = alloca i64,i16 3,align 8 ; x,y,z
    call i32 @read(i32 %fd,i64* %vars_predict,i32 8)

    %x = load i64,i64* %vars_predict,align 8
    %t0 = mul i64 %x,%x
    %t1 = mul i64 %x,%t0
    %t2 = mul i64 %t1,3
    %t3 = mul i64 %x,25
    %t4 = add i64 %t2,%t3
    %t5 = sub i64 %t4,6
    %cond1 = icmp slt i64 %t5,0
    br i1 %cond1,label %b1_2,label %b3_4

b1_2:
    
    call void @pr_debug_blks([9 x i8]* @debug1)

    %py = getelementptr i64,i64* %vars_predict,i16 1
    call i32 @read(i32 %fd,i64* %py,i32 8)
    
    %y = load i64,i64* %py,align 8
    %t6 = shl i64 %y,5
    %t7 = sitofp i64 %t6 to double
    %t8 = fneg double %t7
    %t9 = fptosi double %t8 to i64
    %t10 = xor i64 %t9,70525919
    %t11 = and i64 %t10,70
    %t12 = srem i64 %t11,3
    %cond2 = icmp eq i64 %t12,0
    br i1 %cond2,label %bl2,label %bl1
bl1:
    call void @pr_debug_blk([12 x i8]* @debug3,i64 1)
    store i64 1,i64* %vars,align 8
    %a = load i64,i64* %vars,align 8
    %a_r = shl i64 %a,1
    %pb = getelementptr i64,i64* %vars,i16 1
    store i64 1,i64* %pb,align 8
    %b = load i64,i64* %pb,align 8
    %b_0 = shl i64 %b,2
    %b_r = or i64 %b_0,1
    %pc = getelementptr i64,i64* %vars,i16 2
    store i64 4294967295,i64* %pc,align 8
    %c = load i64,i64* %pc,align 8
    %c_0 = xor i64 %c,4294967287
    %c_1 = shl i64 %c_0,2
    %c_2 = or i64 %c_1,192
    %c_r = sub i64 %c_2,4
    %pd = getelementptr i64,i64* %vars,i16 3
    store i64 1,i64* %pd,align 8
    %d = load i64,i64* %pd,align 8
    %d_0 = shl i64 %d,7
    %d_r = xor i64 %d_0,460
    %pe = getelementptr i64,i64* %vars,i16 4
    store i64 2895579653,i64* %pe,align 8
    %e = load i64,i64* %pe,align 8
    %e_0 = xor i64 %e,2890915820
    %e_1 = sub i64 %e_0,14644771
    %e_2 = sitofp i64 %e_1 to double
    %e_3 = fneg double %e_2
    %e_r = fptosi double %e_3 to i64
    call void @pr_args([39 x i8]* @debugargs,i64 %a_r,i64 %b_r,
    i64 %c_r,i64 %d_r,i64 %e_r)
    %cmp = sub i64 %e_r,1
    br label %bl1.for
bl1.for:
    %counter = phi i64 [0,%bl1],[%counter_m,%bl1.for]
    %e_next = phi i64 [%e_r,%bl1],[%e_next_modif,%bl1.for]
    %e_next_modif = add i64 %e_next,%e_r
    %counter_m = add i64 %counter,1
    %condbl1 = icmp slt i64 %counter,%cmp
    br i1 %condbl1,label %bl1.for,label %bl1.continue
bl1.continue:
    %r_0 = mul i64 %e_next,%d_r
    %r_1 = mul i64 %a_r,%b_r
    %r_2 = add i64 %r_1,%c_r
    %r_r = sub i64 %r_2,%r_0
    br label %exit

bl2:
    call void @pr_debug_blk([12 x i8]* @debug3,i64 2)
    store i64 3442794271,i64* %vars,align 8
    %a2 = load i64,i64* %vars,align 8
    %a2_0 = xor i64 %a2,3442794266
    %a2_r = sub i64 %a2_0,3
    %pb2 = getelementptr i64,i64* %vars,i64 1
    store i64 57248948,i64* %pb2,align 8
    %b2 = load i64,i64* %pb2,align 8
    %b2_0 = xor i64 %b2,4407587
    %b2_1 = and i64 %b2_0,4
    %b2_r = add i64 %b2_1,1
    %pc2 = getelementptr i64,i64* %vars,i64 2
    store i64 988,i64* %pc2,align 8
    %c2 = load i64,i64* %pc2,align 8
    %c2_r = and i64 %c2,255
    %pd2 = getelementptr i64,i64* %vars,i64 3
    store i64 260,i64* %pd2,align 8
    %d2 = load i64,i64* %pd2,align 8
    %d2_0 = or i64 %d2,203
    %d2_r = and i64 %d2_0,332
    %pe2 = getelementptr i64,i64* %vars,i64 4
    store i64 11627287,i64* %pe2,align 8
    %e2 = load i64,i64* %pe2,align 8
    %e2_0 = add i64 %e2,3407820
    %e2_1 = xor i64 %e2_0,14666469
    br label %bl2.for

bl2.for:

    %i = phi i64 [16,%bl2],[%i_m,%bl2.for]
    %el = phi i64 [0,%bl2],[%el_r,%bl2.for]
    %tmp = phi i64 [0,%bl2],[%tmp_r,%bl2.for]
    %e2_r = phi i64 [%e2_1,%bl2],[%e2_m,%bl2.for]
    %el_0 = and i64 %e2_r,255
    %el_r = shl i64 %el_0,%i
    %tmp_r = or i64 %el_r,%tmp
    %e2_m = lshr i64 %e2_r,8
    %i_m = sub i64 %i,8
    %condbl2 = icmp sge i64 %i,0
    br i1 %condbl2,label %bl2.for,label %bl2.continue

bl2.continue:

    %e2_2 = mul i64 %tmp,%tmp

    call void @pr_args([39 x i8]* @debugargs,i64 %a2_r,i64 %b2_r,
    i64 %c2_r,i64 %d2_r,i64 %tmp)

    %r2_0 = mul i64 %e2_2,%d2_r
    %r2_1 = mul i64 %a2_r,%b2_r
    %r2_2 = add i64 %r2_1,%c2_r
    %r2_r = sub i64 %r2_2,%r2_0
    br label %exit
b3_4:

    call void @pr_debug_blks([9 x i8]* @debug2)

    %pz = getelementptr i64,i64* %vars_predict,i16 2
    call i32 @read(i32 %fd,i64* %pz,i32 8)
    %z = load i64,i64* %pz,align 8
    %t13 = xor i64 %z,65494
    %t14 = lshr i64 %t13,2
    %t15 = or i64 %t14,189115999977472
    %t16 = urem i64 %t15,2 
    %b23cond2 = icmp sgt i64 %t16,0
    br i1 %b23cond2,label %bl3,label %bl4
bl3:
    call void @pr_debug_blk([12 x i8]* @debug3,i64 3)
    store i64 203,i64* %vars,align 8
    %c3 = load i64,i64* %vars,align 8
    %c3_0 = or i64 %c3,260
    %c3_1 = and i64 %c3_0,332
    %c3_r = xor i64 %c3_1,400
    %pa3 = getelementptr i64,i64* %vars,i64 0
    store i64 145,i64* %pa3,align 8
    %a3 = load i64,i64* %pa3,align 8
    %a3_0 = xor i64 %a3,255
    %a3_r = sdiv i64 %c3_r,%a3_0
    store i64 63255150,i64* %pa3,align 8
    %b3 = load i64,i64* %pa3,align 8
    %b3_0 = xor i64 %b3,11321050
    %b3_1 = xor i64 %b3_0,4407587
    %b3_2 = and i64 %b3_1,4
    %b3_r = sdiv i64 20,%b3_2
    %pd3 = getelementptr i64,i64* %vars,i64 3
    store i64 297,i64* %pd3,align 8
    %d3 = load i64,i64* %pd3,align 8
    %d3_0 = sdiv i64 %d3,8
    %d3_1 = srem i64 %d3_0,8
    %d3_2 = shl i64 %d3_1,6
    %d3_3 = srem i64 %d3,8
    %d3_4 = shl i64 %d3_3,3
    %d3_5 = or i64 %d3_2,%d3_4
    %d3_6 = sdiv i64 %d3_0,8
    %d3_7 = srem i64 %d3_6,8
    %d3_r = or i64 %d3_7,%d3_5
    store i64 294333,i64* %pd3,align 8
    %e3 = load i64,i64* %pd3,align 8
    %e3_0 = add i64 %e3,102190
    %e3_1 = xor i64 %e3_0,44254
    %e3_2 = sitofp i64 %e3_1 to double
    %e3_3 = fneg double %e3_2
    %e3_4 = fptosi double %e3_3 to i64
    %e3_6 = sub i64 %b3_r,%e3_4 ; right value not decrement
    %e3_7 = add i64 0,4443635
    %e3_8 = xor i64 433902,%e3_7
    %e3_9 = add i64 %d3_r,%e3_8
    %e3_10 = sub i64 %e3_9,4109359
    %e3_r = mul i64 %e3_10,%e3_6

    call void @pr_args([39 x i8]* @debugargs,i64 %a3_r,i64 %b3_r,
    i64 %c3_r,i64 %d3_r,i64 %e3_r)

    %r3_0 = mul i64 %a3_r,%b3_r
    %r3_1 = mul i64 %e3_r,%d3_r
    %r3_2 = add i64 %r3_0,%c3_r
    %r3_r = sub i64 %r3_2,%r3_1
    br label %exit
bl4:
    call void @pr_debug_blk([12 x i8]* @debug3,i64 4)
    store i64 -2,i64* %vars,align 8
    %a4 = load i64,i64* %vars,align 8
    %a4_0 = sitofp i64 %a4 to double
    %a4_1 = fneg double %a4_0
    %a4_r = fptosi double %a4_1 to i64
    store i64 25,i64* %vars,align 8
    %b4 = load i64,i64* %vars,align 8
    %b4_r = udiv i64 %b4,5
    %pc4 = getelementptr i64,i64* %vars,i64 1
    store i64 542,i64* %pc4,align 8
    %c4 = load i64,i64* %pc4,align 8
    %c4_0 = mul i64 %c4,5
    %c4_1 = xor i64 %c4_0,2766
    %c4_2 = sdiv i64 %c4_1,8
    %c4_3 = sdiv i64 %c4_2,8
    %c4_4 = srem i64 %c4_3,8
    %c4_5 = shl i64 %c4_4,3 
    %c4_5_1 = add i64 42,46
    %c4_6 = sdiv i64 %c4_5_1,8
    %c4_7 = srem i64 %c4_6,8
    %c4_8 = shl i64 %c4_7,6 
    %c4_9 = add i64 255,0
    %c4_10 = xor i64 %c4_9,254
    %c4_11 = sub i64 %c4_10,1
    %c4_12 = or i64 %c4_5,%c4_11
    %c4_13 = or i64 %c4_12,%c4_8 ; or result
    %c4_14 = add i64 0,103
    %c4_15 = add i64 %c4_14,81
    %c4_16 = xor i64 %c4_15,172
    %c4_r = add i64 %c4_16,%c4_13
    call void asm "nop;nop;nop",""()
    br label %bl4.for1

bl4.for1:

    %tmp1 = phi i64 [0,%bl4],[%tmp1_m,%bl4.for1]
    %i4 = phi i64 [0,%bl4],[%i4_m,%bl4.for1]
    %d4_r = phi i64 [258010843790042,%bl4],[%d4_m,%bl4.for1]
    %temp0 = srem i64 %d4_r,8
    %tmp1_m = add i64 %temp0,%tmp1
    %d4_m = sdiv i64 %d4_r,8
    %i4_m = add i64 %i4,1
    %condbl4 = icmp slt i64 %i4,16
    br i1 %condbl4,label %bl4.for1,label %bl4.continue
bl4.continue:
    %tmp_0 = add i64 16116873,0
    %tmp_1 = add i64 %tmp_0,234343
    %tmp4_init = xor i64 %tmp_1,16768970 ;tyt
    br label %bl4.for2
bl4.for2:
    %tmp4 = phi i64 [%tmp4_init,%bl4.continue],
    [%tmp4_m,%bl4._blif]
    %addr = phi i8* [blockaddress(@main,%bl4.for2.con_phi),
    %bl4.continue],
    [blockaddress(@main,%bl4.for2.continue),%bl4._blif]
    indirectbr i8* %addr,[label %bl4.for2.con_phi,
    label %bl4._blif]
bl4.for2.con_phi:
    %i4_2 = phi i64 [0,%bl4.for2],[%i4_2m,%bl4.incfor2]
    %tmp2 = phi i64 [9539649576,%bl4.for2],[%tmp2_2,%bl4.incfor2]
    %tmp3 = phi i64 [0,%bl4.for2],[%tmp3_2,%bl4.incfor2]

    %i4_if = srem i64 %i4_2,10
    %ifcond4 = icmp eq i64 %i4_if,2
    br i1 %ifcond4,label %bl4._blif,label %bl4.for2.continue
bl4._blif:
    %tmp4_m = mul i64 %tmp4,%tmp4
    br label %bl4.for2
bl4.for2.continue:

    %condfor2 = icmp slt i64 %i4_2,3
    br i1 %condfor2,label %bl4.for3,label %bl4.continue2

bl4.for3:

    %j = phi i64 [0,%bl4.for2.continue],[%j_next,%bl4.for3]
    %tmp2_2 = phi i64 [%tmp2,%bl4.for2.continue],[%tmp2_2m,%bl4.for3]
    %tmp3_2 = phi i64 [%tmp3,%bl4.for2.continue],[%tmp3_2m,%bl4.for3]
    
    %temp2_0 = srem i64 %tmp2_2,10
    %tmp3_2m = add i64 %temp2_0,%tmp3_2
    %tmp2_2m = sdiv i64 %tmp2_2,10

    %j_next = add i64 %j,1

    %for3condbl4 = icmp slt i64 %j,10
    br i1 %for3condbl4,label %bl4.for3,label %bl4.incfor2
bl4.incfor2:

    %i4_2m = add i64 %i4_2,1
    br label %bl4.for2.con_phi
bl4.continue2:

    %r4_0 = mul i64 %b4_r,%a4_r
    %r4_1 = add i64 %c4_r,%r4_0
    %r4_2 = add i64 %tmp1,%tmp1
    %r4_3 = add i64 %r4_2,%tmp3
    %r4_4 = add i64 %r4_3,157

; log

    %ifequal = icmp eq i64 %tmp4,%r4_4
	%eval = zext i1 %ifequal to i64
    call void @pr_args([39 x i8]* @debugargs,i64 %a4_r,i64 %b4_r,
    i64 %c4_r,i64 %d4_r,i64 %eval)

; end log

    %r4_5 = mul i64 %tmp4,%r4_4
    %r4_r = sub i64 %r4_1,%r4_5
    br label %exit
exit:

    %rr64 = phi i64 [%r_r,%bl1.continue],
    [%r2_r,%bl2.continue], [%r3_r,%bl3],
    [%r4_r,%bl4.continue2]
    call void @pr_debug_result([15 x i8]* @debugr,i64 %rr64)
    %rr = trunc i64 %rr64 to i32
    ret i32 %rr
}
```
ну а это вам на разбор)

***Эпилог и заключение***

Непрозрачные предикаты - это самый сложный метод обфускации в CFG.Мы узнали что предикаты делятся на разные типы и классы ,что они способны делать не возможным статический и затруднять сильно динамический анализ.Особенно если предикаты непрозрачные используются в виртуализации или в jitting obfuscation.Но это уже другие совсем темы.Надеюсь я смог помочь ,разобраться в этой теме 8).

автор: sh4m2hwz
