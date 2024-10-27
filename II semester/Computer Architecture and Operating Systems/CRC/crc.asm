section .bss
    buffer resb 65539                           ;tworzenie bufora o rozmiarze najwiekszego mozliwego fragmentu
                                                ;z uwzglednieniem 4 bajtow na przesuniecie
section .text
    global _start

_start:
    cmp QWORD [rsp], 3                          ;test czy zostały podane trzy argumenty
    jne _blad
    mov rdi, QWORD [rsp + 16]                   ;przypisanie adresu pliku do rdi
    mov rsi, [rsp + 24]                         ;przypisanie wielomianu do rsi
    xor r12, r12

    mov r8b, byte [rsi]                         ;test czy wielomian nie jest stały
    cmp r8b, 0
    je _blad

    xor rcx, rcx
_transforming_string_loop:                      ;zamiana stringa na liczbe go reprezentującą
    mov r8b, byte [rsi + rcx]
    cmp r8b, 0                                  ;sprawdzenie czy dany znak jest nullem
    je _normalizacja_dzielnika                  ;oznacza to koniec stringa do wczytania
    sub r8b, 48                                 ;przeksztalcenie z kodu ascii na bit odpowiadajacy mu
    cmp r8b, 1                                  ;test czy liczba to 1 lub 0
    ja _blad
    movzx r9, r8b
    shl r10, 1                                  ;przesuniecie r10
    add r10, r9                                 ;wpisanie na ostatnie miejsce bitu 0 lub 1
    inc rcx                                     ;zwiekszenie licznika
    jmp _transforming_string_loop


_normalizacja_dzielnika:                        ;przesuniecie znaczacych bitow dzielnika do 'lewej' strony
    movzx r15, cl                               ;zapisanie ilosci bajtow dzielnika
    mov r8b, cl
    mov cl, 64
    sub cl, r8b                                 ;obliczenie o ile nalezy przesunac liczbe w lewo
    shl r10, cl                                 ;przesuniecie o ta liczbe

    mov rsi, 0                                  ;otwarcie pliku
    mov rax, 2
    syscall

    test rax, rax                               ;test czy otwarcie wykonane prawidlowo
    js _blad

    mov r9, rax                                 ;przypisanie deskryptora pliku do r9

    mov rax, 8                                  ;zapisanie aktualnej pozycji wskaźnika (sys_lseek)
    mov rdi, r9
    mov rsi, 0
    mov rdx, 0
    syscall

_obsluz_fragment:                               ;wczytanie i analiza pojedynczego fragmentu
    mov r13, rax
    mov rsi, buffer
    mov rdx, 2
    mov rax, 0
    syscall                                     ;wczytanie dlugosci fragmentu

    test rax, rax
    js _blad

    mov r8w, word [rsi]                         ;zapisanie dlugosci fragmentu w r8w

    mov rdi, r9                                 ;przypisanie deskryptora
    mov rsi, buffer                             ;przypisanie buffera
    mov rbx, buffer
    movzx rdx, r8w                              ;rdx przechowuje teraz dlugosc fragmentu
    add rbx, rdx                                ;rbx wskazuje na 4 baity oznaczajace przesuniecie
    add rdx, 4                                  ;zwiekszamy dlugosc o 4
    mov rax, 0
    syscall                                     ;wczytanie pozostalej czesci fragmentu

    test rax, rax
    js _blad

    movsxd rsi, dword [rbx]                     ;przypisanie wartosci przesuniecia do rsi
    cmp r8w, 0                                  ;test czy fragment mial dlugosc niezerowa
    je _crc_wyjscie                             ;jezeli mial to pomijamy wykonwyanie crc dla niego

_crc_start:
    ;r10 - dzielnik
    ;rbx - suma
    xor rcx, rcx
_petla_bajt:                                    ;wykonaj r8w razy czyli dlugosc framgentu
    mov al, [buffer + rcx]
    push rcx
    mov rcx, 8

_petla_Bit:                                     ;wykonaj dla kazdego bitu
    rcl al, 1
    rcl r12, 1
    jnc _notXor
    xor r12, r10
_notXor:
    loop _petla_Bit

    pop rcx
    inc rcx
    cmp cx, r8w
    jne _petla_bajt
    jmp _crc_wyjscie

_crc_wyjscie:
    mov rax, 8
    mov rdi, r9
    mov rdx, 1
    syscall                                     ;odczytanie biezacej pozycji kursora

    cmp rax, r13                                ;test czy fragment wskazuje na siebie
    jne _obsluz_fragment                        ;petla jezeli nie

_zakmniecie_pliku:
    mov rdi, rax
    mov rax, 3
    syscall

    mov rcx, 64
_normalizacja_wyniku:                           ;rotacja wyniku 64
    clc
    rcl r12, 1
    jnc _notXor2
    xor r12, r10
_notXor2:
    loop _normalizacja_wyniku

_przygotowanie_wyniku:                          ;zamiana wyniku na string w buffer
    mov rsi, buffer                             ;ustawienie rsi na buffor
    xor rcx, rcx                                ;wyzerowanie licznika

_petla_przygotowania:
    shl r12, 1                                  ;najbardziej znaczacy bit do carryFlag
    setc bl
    movzx rax, bl
    add bl, 48                                  ;zamiana na kod ASCII
    mov [rsi], bl                               ;wpisanie do buffera
    inc rcx
    inc rsi
    cmp rcx, r15
    jne _petla_przygotowania

    mov byte [rsi], 10                          ;dopisanie znaku konca linii
    inc r15

    mov rsi, buffer
    mov rdx, r15
    mov rdi, 1
    mov rax, 1
    syscall                                     ;wypisanie wyniku

_koniec_programu:
    mov rax, 60
    xor rdi, rdi
    syscall

_blad:
    mov rax, 60                      ; numer wywołania systemowego sys_exit
    mov rdi, 1                       ; kod wyjścia 1
    syscall