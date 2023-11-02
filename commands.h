DEF_CMD (push, 1, 1, PUSH (*GetArgument (code_array, &position_in_code_array, "push",
                                         main_spu.RAM, main_spu.regs));)


DEF_CMD (pop, 2, 1, *(GetArgument (code_array, &position_in_code_array, "pop",
                                         main_spu.RAM, main_spu.regs)) = POP;)

DEF_CMD (add, 3, 0, PUSH (POP + POP);
                    position_in_code_array++;)

DEF_CMD (sub, 4, 0, double first_num = POP;
                    double second_num = POP;
                    PUSH (first_num - second_num);
                    position_in_code_array++;)

DEF_CMD (mul, 5, 0, PUSH (POP * POP);
                    position_in_code_array++;)

DEF_CMD (div, 6, 0, double first_num = POP;
                    double second_num = POP;
                    PUSH (first_num / second_num);
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

DEF_JMP (jmp, 12, 1)

DEF_COND_JMP (ja, 13, 1, IsDoubleLess)

DEF_COND_JMP (jae, 14, 1, IsDoubleLessOrEqual)

DEF_COND_JMP (jb, 15, 1, !IsDoubleLess)

DEF_COND_JMP (jbe, 16, 1, !IsDoubleLessOrEqual)

DEF_COND_JMP (je, 17, 1, IsDoubleEqual)

DEF_COND_JMP (jne, 18, 1, !IsDoubleEqual)
