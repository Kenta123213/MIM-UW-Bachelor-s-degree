global mdiv
mdiv:
    ;rdi, rsi, r11, rcx
    ;tablica, rozmiar tablicy, dzielnik, iterator petli
    ;r8, r9
    ;znak dzielnej, znak dzielnika

    xor r8, r8                               ;przypisanie wartosci poczatkowych
    xor r9, r9
    mov r11, rdx
    xor rdx, rdx

    cmp qword [rdi + 8 * (rsi - 1)], 0      ;sprawdzenie czy dzielna ujemna
    jns .positive_dividend                  ;skok jezeli dodatnia

.normalizing_dividend:                      ;zmiana znaku dzielnej na dodatni
    inc r8                                  ;oznaczamy ze dzielna byla ujemna
.negation:
    mov rcx, rsi                            ;ustawienie iteratora 1
    xor r10, r10                            ;ustawienie iteratora 2
    stc                                     ;ustawienie carry flag na 1
.negation_loop:
    not qword [rdi + 8 * r10]
    adc qword [rdi + 8 * r10], 0	    ;dodanie 1 jeżeli carry flag to 1
    inc r10
    loop .negation_loop
    cmp rdx, 0                              ;sprawdzenie z ktorego miejsca zostalo wywolane .negation
    jne .same_sign

.positive_dividend:
    cmp r11, 0                              ;test czy dzielnik dodatni
    jns .positive_divider
    inc r9                                  ;oznaczamy ze dzielnik ujemny
    neg r11                                 ;zmiana znaku

.positive_divider:
    mov rcx, rsi                            ;ustawienie iteratora

.division_loop:
    mov rax, qword [rdi + 8 * (rcx - 1)]    ;przepisanie liczby z tablicy do rax
    div r11                                 ;dzielenie
    mov qword [rdi + 8 * (rcx - 1)], rax    ;zastapienie liczby w tablicy wynikiem z dzielenia
    loop .division_loop

    XCHG rax, rdx                           ;przypisanie reszty z dzielenia do rax

    cmp r8, r9                              ;sprawdzenie czy dzielna i dzielnik maja rozne znaki
    je .check_for_overflow                  ;skok do check_for_overflow jezeli maja takie same znaki

.result_negation:
    xor rdx, rdx
    inc rdx                                 ;ustawienie rdx na 1
    jmp .negation

.check_for_overflow:
    cmp qword [rdi + 8 * (rsi - 1)], 0      ;test czy pierwszy bit ustawiony na 1
    jns .same_sign

    div rcx                                 ;zwrocenie overflow (wiadomo ze rcx to 0)

.same_sign:
    cmp r8, 0                               ;test czy dzielnik byl ujemny
    je .end                                 ;skok jezeli byl dodatni

.reminder_negation:                         ;negacja reszty
    neg rax

.end:
    ret
