static inline bool
b_atoi(
    const char* str, 
    int mode, 
    char target, 
    uint64_t flags, 
    uint8_t* flag_src,
    AtoiCtx* actx)
{
    actx->expr_size = 0;
    // int64_t* v_target = &(actx->expr[0].term.value);
    #define TARGET_SW_VAL(t) t = &(actx->expr[actx->expr_size].term.value)
    #define TARGET_SW_MOD(t) t = &(actx->expr[actx->expr_size].term.mod)
    #define TARGET_SW_MULT(t) t = &(actx->expr[actx->expr_size].term.mult)
    #define TARGET_APPLY(t, v) *t = v
    #define ATOM_INCR() actx->expr_size++
    #define GET_ATOM() (actx->expr[actx->expr_size])
    #define GET_TERM() (actx->expr[actx->expr_size].term)
    #define GET_OP() (actx->expr[actx->expr_size].op)
    int64_t* v_target;
    TARGET_SW_VAL(v_target);
    int64_t acc = 0;
    int64_t m = 0;
    int64_t incr = 0;

    char stracc[100];
    int stri=0;
    bool status = true;

    // int64_t* v_target = &(actx->output);

    char c = '\0';
    char prev = '\0';
    uint16_t status_flags = JUST_BEGAN;

    loop:
    switch(mode)
    {
        case 1:
            status = (c = str[incr++]) && c != target;
            break;
        case 2:
            status =    (c = str[incr++]) 
                     && !MAP_CHECK_FLAG(flag_src, c, flags);
            break;
    }
    if(!status) goto end;

    if(!isdigit(c))
    {
        switch(c)
        {
            case '$':
                if(stat)
            case '%':
                if((status_flags & JUST_GOT_DIGIT) && stri)
                {
                    stracc[stri] = '\0';
                    TARGET_APPLY(v_target, (atoi(stracc)));
                    stri = 0; 
                    status_flags &= ~JUST_GOT_DIGIT;
                    TARGET_SW_MOD(v_target);
                }
                else
                {
                    actx->err = true;
                    goto end;
                }
                break;
            case 'B':
                if((status_flags & (JUST_FINISHED_OP | TERM_CURR)) &&
                    !JUST_GOT_DIGIT)
                {
                    status_flags &= ~JUST_FINISHED_OP;
                    status_flags |= TERM_CURR;
                    GET_TERM().amt = 3;
                    TARGET_SW_VAL(v_target);
                }
                else if(status_flags & JUST_BEGAN)
                {
                    status_flags &= ~JUST_BEGAN;
                    status_flags |= TERM_CURR;
                    GET_TERM().amt = 3;
                    TARGET_SW_VAL(v_target);
                }
                else
                {
                    actx->err = true;
                    goto end;
                }
            case '-':
                if(status_flags & JUST_BEGAN)
                {
                    status_flags |= (TERM_CURR);
                    status_flags ^= JUST_BEGAN;
                    GET_TERM().mult = -1;
                    TARGET_SW_VAL(v_target);
                    break;
                }
            case '+':
                if(status_flags & JUST_FINISHED_OP)
                {
                    actx->err = true;
                    goto end;
                }
                else if(stri && (status_flags & TERM_CURR))
                {
                    stracc[stri] = '\0';
                    TARGET_APPLY(v_target, (atoi(stracc)));
                    stri = 0;
                    ATOM_INCR();
                    GET_OP().op_flags = (c == '-') ? MINUS_OP : PLUS_OP;
                    GET_ATOM().type = OP_TYPE;
                    ATOM_INCR();
                    status_flags = JUST_FINISHED_OP;
                }
                else
                {
                    actx->err = true;
                    goto end;
                }
                break;
        }
    }
    // else
    // {
    //     stracc
    // }

    prev = c;
    end:
    if(stri)
    {
        stracc[stri] = '\0';
        *v_target = (int64_t) atoi(stracc);
    }
    return true;
}