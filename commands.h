DEF_CMD (push, 1, 1, PUSH (*GetArgument (code_array, &position_in_code_array, "push",
                                         main_spu.RAM, main_spu.regs));)


DEF_CMD (pop, 2, 1, *(GetArgument (code_array, &position_in_code_array, "pop",
                                         main_spu.RAM, main_spu.regs)) = POP;)

DEF_CMD (add, 3, 0, PUSH (POP + POP);
                    position_in_code_array++;)

DEF_CMD (sub, 4, 0, PUSH (POP - POP);
                    position_in_code_array++;)

DEF_CMD (mul, 5, 0, PUSH (POP * POP);
                    position_in_code_array++;)

DEF_CMD (div, 6, 0, PUSH (POP / POP);
                    position_in_code_array++;)

DEF_CMD (in, 7, 0,  double num_to_in = 0;
                    scanf ("%lf", &num_to_in);
                    PUSH (num_to_in);
                    position_in_code_array++;)

DEF_CMD (out, 8, 0, printf ("%lf\n", POP);
                    position_in_code_array++;)

DEF_CMD (sqrt, 9, 0, PUSH (sqrt (POP));
                     position_in_code_array++;)


DEF_CMD (sin, 10, 0, PUSH (sin (POP));
                     position_in_code_array++;)

DEF_CMD (cos, 11, 0, PUSH (cos (POP));
                     position_in_code_array++;)

DEF_CMD (hlt, -1, 0, return SPU_FUNC_FAIL;)

DEF_JMP (jmp, 12,   position_in_code_array = (size_t) code_array[position_in_code_array + 1];
                    printf("AAAA %Iu\n", position_in_code_array);)

DEF_COND_JMP (ja, 13, >)

DEF_COND_JMP (jae, 14, >=)

DEF_COND_JMP (ja, 15, <)

DEF_COND_JMP (jb, 16, >)

DEF_COND_JMP (jbe, 17, <=)

DEF_COND_JMP (je, 18, ==)

DEF_COND_JMP (jne, 19, !=)
