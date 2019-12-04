#include "inc/reedsolomoncoding.h"

inline int max(int a,int b){
    return (((a) > (b)) ? (a) : (b));
}

void ReedSolomonCoding::generate_gf(void){
    int i,mask = 1;
    alpha_to[M] = 0;
    for (i = 0; i < M; i++){
        alpha_to[i] = mask;
        index_of[alpha_to[i]] = i;
        if (pp[i] != 0)
            alpha_to[M] ^= mask;
        mask <<= 1;
    }
    index_of[alpha_to[M]] = M;
    mask >>= 1;
    for (i = M + 1; i < LENGTH_WORD; i++){
        if (alpha_to[i - 1] >= mask)
            alpha_to[i] = alpha_to[M] ^ ((alpha_to[i - 1] ^ mask) << 1);
        else
            alpha_to[i] = alpha_to[i - 1] << 1;
        index_of[alpha_to[i]] = i;
    }
    index_of[0] = 0xff;
    alpha_to[0xff] = 0;
}
void ReedSolomonCoding::gen_poly(unsigned short TT, unsigned char *g){
    int i, j;
    g[0] = 2;    /* primitive element alpha = 2  for GF(2**M)  */
    g[1] = 1;    /* g(x) = (X+alpha) initially */
    for (i = 2; i <= 2 * TT; i++)
    {
        g[i] = 1;
        for (j = i - 1; j > 0; j--)
            if (g[j] != 0)
                g[j] = g[j - 1] ^ alpha_to[(index_of[g[j]] + i) % LENGTH_WORD];
            else
                g[j] = g[j - 1];
        g[0] = alpha_to[(index_of[g[0]] + i) % LENGTH_WORD];     /* g[0] can never be zero */
    }
    /* convert g[] to index form for quicker encoding */
    for (i = 0; i <= 2 * TT; i++)
        g[i] = index_of[g[i]];
}
void ReedSolomonCoding::encode_rs(unsigned char* address, char rsDeepness){
    unsigned short TT = (rsDeepness ? Ts : Tn);
    short KK = (rsDeepness ? Ks : Kn);
    unsigned char *data_address = &address[TT * 2];
    unsigned char *g = (rsDeepness ? gs : gn);

    int i, j;

    for (i = 0; i < 2 * TT; i++)
        address[i] = 0;

    for (i = KK - 1; i >= 0; i--)
    {
        int feedback = index_of[data_address[i] ^ address[2 * TT - 1]];
        if (feedback != 0xff)
        {
            for (j = 2 * TT - 1; j > 0; j--)
                if (g[j] != 0xff)
                    address[j] = address[j - 1] ^ alpha_to[(g[j] + feedback) % LENGTH_WORD];
                else
                    address[j] = address[j - 1];
            address[0] = alpha_to[(g[0] + feedback) % LENGTH_WORD];
        }
        else
        {
            for (j = 2 * TT - 1; j > 0; j--)
                address[j] = address[j - 1];
            address[0] = 0;
        }
    }
}
/* NASA Voyager (255,223) */
int ReedSolomonCoding::decode_rs_nasa(unsigned char* recd){
    int i, j;
    /* переводим recd[i] в индексную форму */
    for (i = 0; i < LENGTH_WORD; i++)
        recd[i] = index_of[recd[i]];

    /*
       1) формируем синдромы ошибок в s[]
    */
    bool syn_error = false;
    int s[2 * Tn + 1];
    for (int i = 1; i <= 2 * Tn; i++)
    {
        s[i] = 0;
        for (j = 0; j < LENGTH_WORD; j++)
            if (recd[j] != 0xff)
                s[i] ^= alpha_to[(recd[j] + i * j) % LENGTH_WORD]; /* recd[j] в индексной форме */
        if (s[i] != 0)
            syn_error = true;        /* установить флаг ошибки */
        /* преобразовать синдром из полиномиальной в индексную форму */
        s[i] = index_of[s[i]];
    }

    if (!syn_error)       /* нет ненулевых синдромов => ошибок нет */
    {
        for (i = 0; i < LENGTH_WORD; i++)        /* преобразвать recd[] обратно */
            recd[i] = alpha_to[recd[i]];
        return 0;
    }

    /* есть ошибки, пытаемся исправить */

/*
   2) Вычисляем полином локатора ошибки с помощью итеративного алгоритма Берлекампа

   d[u]   'мю'-тое расхождение, где u='мю'+1 и 'мю' номер шага от -1 до 2*T,
   l[u]   степень elp на данном шаге, и
   u_l[u] разница между номером шага и степенью elp.
*/

    int elp[2 * Tn + 2][2 * Tn], d[2 * Tn + 2], l[2 * Tn + 2], u_lu[2 * Tn + 2];
    /* инициализация таблицы */
    d[0] = 0;			/* индексная форма */
    d[1] = s[1];		/* индексная форма */
    elp[0][0] = 0;		/* индексная форма */
    elp[1][0] = 1;		/* полиномиальная форма */
    for (i = 1; i < 2 * Tn; i++)
    {
        elp[0][i] = -1;	/* индексная форма */
        elp[1][i] = 0;	/* полиномиальная форма */
    }
    l[0] = 0;
    l[1] = 0;
    u_lu[0] = -1;
    u_lu[1] = 0;

    int u = 0;
    do
    {
        u++;
        if (d[u] == 0xff)
        {
            l[u + 1] = l[u];
            for (i = 0; i <= l[u]; i++)
            {
                elp[u + 1][i] = elp[u][i];
                elp[u][i] = index_of[elp[u][i]];
            }
        }
        else		/* ищем слова с наибольшим u_lu[q] для которых d[q]!=0 */
        {
            int q = u - 1;
            while ((d[q] == 0xff) && (q > 0))
                q--;
            /* найден первый ненулевой d[q]  */
            if (q > 0)
            {
                int j = q;
                do
                {
                    j--;
                    if ((d[j] != -1) && (u_lu[q] < u_lu[j]))
                        q = j;
                } while (j > 0);
            }

            /* найден q такой, что d[u]!=0 и u_lu[q] максимально */
            /* запишем степень нового elp полинома */
            l[u + 1] = max(l[u], l[q] + u - q);

            /* формируем новый elp(x) */
            for (i = 0; i < 2 * Tn; i++)
                elp[u + 1][i] = 0;
            for (i = 0; i <= l[q]; i++)
                if (elp[q][i] != -1)
                    elp[u + 1][i + u - q] = alpha_to[(d[u] + LENGTH_WORD - d[q] + elp[q][i]) % LENGTH_WORD];
            for (i = 0; i <= l[u]; i++)
            {
                elp[u + 1][i] ^= elp[u][i];
                elp[u][i] = index_of[elp[u][i]];  /* старый elp - в индексную форму */
            }
        }
        u_lu[u + 1] = u - l[u + 1];

        /* формируем 'мю'-тое расхождение */
        if (u < 2 * Tn)    /* на последней итерации расхождение не было обнаружено */
        {
            if (s[u + 1] != 0xff)
                d[u + 1] = alpha_to[s[u + 1]];
            else
                d[u + 1] = 0;
            for (i = 1; i <= l[u + 1]; i++)
                if ((s[u + 1 - i] != 0xff) && (elp[u + 1][i] != 0))
                    d[u + 1] ^= alpha_to[(s[u + 1 - i] + index_of[elp[u + 1][i]]) % LENGTH_WORD];
            d[u + 1] = index_of[d[u + 1]];	/* d[u+1] в индексную форму */
        }
    } while ((u < 2 * Tn) && (l[u + 1] <= Tn));

    /* Вычисление локатора ошибки завершено */

    ++u;
    if (l[u] > Tn)		/* степень elp >T - решение невозможно */
    {
        for (i = 0; i < LENGTH_WORD; i++)
            recd[i] = alpha_to[recd[i]];
        return 3;		/* флаг ошибки */
    }

    /* можно исправить ошибки */
    for (i = 0; i <= l[u]; i++)	/* elp в индексную форму */
        elp[u][i] = index_of[elp[u][i]];

    /*
       3) находим корни полинома локатора ошибки
     */

    int reg[Tn + 1];
    for (i = 1; i <= l[u]; i++)
        reg[i] = elp[u][i];

    int count = 0;
    int root[Tn], loc[Tn];
    for (i = 1; i <= LENGTH_WORD; i++)
    {
        int q = 1;
        for (j = 1; j <= l[u]; j++)
            if (reg[j] != 0xff)
            {
                reg[j] = (reg[j] + j) % LENGTH_WORD;
                q ^= alpha_to[reg[j]];
            }
        if (!q)        /* записываем корень и индекс номера локатора ошибки */
        {
            root[count] = i;
            loc[count] = LENGTH_WORD - i;
            count++;
        }
    }
    if (count != l[u])    /* количество корней != степени elp => >T ошибок, решение невозможно */
    {
        for (i = 0; i < LENGTH_WORD; i++)
            recd[i] = alpha_to[recd[i]];	/* преобразвать recd[] обратно */
        return 2;
    }

    /* количество корней == степени elp следовательно кол. ошибок <= T */

    /* формируем полином z(x) */
    int z[Tn + 1];
    for (i = 1; i <= l[u]; i++)	/* Z[0] = 1 всегда */
    {
        if ((s[i] != 0xff) && (elp[u][i] != -1))
            z[i] = alpha_to[s[i]] ^ alpha_to[elp[u][i]];
        else if ((s[i] != 0xff) && (elp[u][i] == -1))
            z[i] = alpha_to[s[i]];
        else if ((s[i] == 0xff) && (elp[u][i] != -1))
            z[i] = alpha_to[elp[u][i]];
        else
            z[i] = 0;
        for (j = 1; j < i; j++)
            if ((s[j] != 0xff) && (elp[u][i - j] != -1))
                z[i] ^= alpha_to[(elp[u][i - j] + s[j]) % LENGTH_WORD];
        z[i] = index_of[z[i]];		/* в индексную форму */
    }

    /*
       4) вычисляем ошибки в позициях loc[i] и исправляем их
    */

    int err[LENGTH_WORD];
    for (i = 0; i < LENGTH_WORD; i++)
    {
        err[i] = 0;
        recd[i] = alpha_to[recd[i]];
    }
    for (i = 0; i < l[u]; i++)	/* сначала вычисляем числитель ошибки */
    {
        err[loc[i]] = 1;			/* accounts for z[0] */
        for (j = 1; j <= l[u]; j++)
            if (z[j] != 0xff)
                err[loc[i]] ^= alpha_to[(z[j] + j * root[i]) % LENGTH_WORD];
        if (err[loc[i]] != 0)
        {
            err[loc[i]] = index_of[err[loc[i]]];
            int q = 0;				/* формируем знаменатель */
            for (j = 0; j < l[u]; j++)
                if (j != i)
                    q += index_of[1 ^ alpha_to[(loc[j] + root[i]) % LENGTH_WORD]];
            q = q % LENGTH_WORD;
            err[loc[i]] = alpha_to[(err[loc[i]] - q + LENGTH_WORD) % LENGTH_WORD];
            recd[loc[i]] ^= err[loc[i]]; /* исправляем ошибку */
        }
    }
    return 1;
}

/* Shortened code (255,249) -> (28,22) */
int ReedSolomonCoding::decode_rs_short(unsigned char* recd)

{
    int i, j;
    /* переводим recd[i] в индексную форму */
    for (i = 0; i < 255; i++)
        recd[i] = index_of[recd[i]];

    /*
       1) формируем синдромы ошибок в s[]
    */
    bool syn_error = false;
    int s[2 * Ts + 1];
    for (int i = 1; i <= 2 * Ts; i++)
    {
        s[i] = 0;
        for (j = 0; j < 255; j++)
            if (recd[j] != 0xff)
                s[i] ^= alpha_to[(recd[j] + i * j) % 255]; /* recd[j] в индексной форме */
        if (s[i] != 0)
            syn_error = true;        /* установить флаг ошибки */
        /* преобразовать синдром из полиномиальной в индексную форму */
        s[i] = index_of[s[i]];
    }

    if (!syn_error)       /* нет ненулевых синдромов => ошибок нет */
    {
        for (i = 0; i < 255; i++)        /* преобразвать recd[] обратно */
            recd[i] = alpha_to[recd[i]];
        return 0;
    }

    /* есть ошибки, пытаемся исправить */

/*
   2) Вычисляем полином локатора ошибки с помощью итеративного алгоритма Берлекампа

   d[u]   'мю'-тое расхождение, где u='мю'+1 и 'мю' номер шага от -1 до 2*Ts,
   l[u]   степень elp на данном шаге, и
   u_l[u] разница между номером шага и степенью elp.
*/

    int elp[2 * Ts + 2][2 * Ts], d[2 * Ts + 2], l[2 * Ts + 2], u_lu[2 * Ts + 2];
    /* инициализация таблицы */
    d[0] = 0;			/* индексная форма */
    d[1] = s[1];		/* индексная форма */
    elp[0][0] = 0;		/* индексная форма */
    elp[1][0] = 1;		/* полиномиальная форма */
    for (i = 1; i < 2 * Ts; i++)
    {
        elp[0][i] = -1;	/* индексная форма */
        elp[1][i] = 0;	/* полиномиальная форма */
    }
    l[0] = 0;
    l[1] = 0;
    u_lu[0] = -1;
    u_lu[1] = 0;

    int u = 0;
    do
    {
        u++;
        if (d[u] == 0xff)
        {
            l[u + 1] = l[u];
            for (i = 0; i <= l[u]; i++)
            {
                elp[u + 1][i] = elp[u][i];
                elp[u][i] = index_of[elp[u][i]];
            }
        }
        else		/* ищем слова с наибольшим u_lu[q] для которых d[q]!=0 */
        {
            int q = u - 1;
            while ((d[q] == 0xff) && (q > 0))
                q--;
            /* найден первый ненулевой d[q]  */
            if (q > 0)
            {
                int j = q;
                do
                {
                    j--;
                    if ((d[j] != -1) && (u_lu[q] < u_lu[j]))
                        q = j;
                } while (j > 0);
            }

            /* найден q такой, что d[u]!=0 и u_lu[q] максимально */
            /* запишем степень нового elp полинома */
            l[u + 1] = max(l[u], l[q] + u - q);

            /* формируем новый elp(x) */
            for (i = 0; i < 2 * Ts; i++)
                elp[u + 1][i] = 0;
            for (i = 0; i <= l[q]; i++)
                if (elp[q][i] != -1)
                    elp[u + 1][i + u - q] = alpha_to[(d[u] + 255 - d[q] + elp[q][i]) % 255];
            for (i = 0; i <= l[u]; i++)
            {
                elp[u + 1][i] ^= elp[u][i];
                elp[u][i] = index_of[elp[u][i]];  /* старый elp - в индексную форму */
            }
        }
        u_lu[u + 1] = u - l[u + 1];

        /* формируем 'мю'-тое расхождение */
        if (u < 2 * Ts)    /* на последней итерации расхождение не было обнаружено */
        {
            if (s[u + 1] != 0xff)
                d[u + 1] = alpha_to[s[u + 1]];
            else
                d[u + 1] = 0;
            for (i = 1; i <= l[u + 1]; i++)
                if ((s[u + 1 - i] != 0xff) && (elp[u + 1][i] != 0))
                    d[u + 1] ^= alpha_to[(s[u + 1 - i] + index_of[elp[u + 1][i]]) % 255];
            d[u + 1] = index_of[d[u + 1]];	/* d[u+1] в индексную форму */
        }
    } while ((u < 2 * Ts) && (l[u + 1] <= Ts));

    /* Вычисление локатора ошибки завершено */

    ++u;
    if (l[u] > Ts)		/* степень elp >Ts - решение невозможно */
    {
        for (i = 0; i < 255; i++)
            recd[i] = alpha_to[recd[i]];
        return 3;		/* флаг ошибки */
    }

    /* можно исправить ошибки */
    for (i = 0; i <= l[u]; i++)	/* elp в индексную форму */
        elp[u][i] = index_of[elp[u][i]];

    /*
       3) находим корни полинома локатора ошибки
     */

    int reg[Ts + 1];
    for (i = 1; i <= l[u]; i++)
        reg[i] = elp[u][i];

    int count = 0;
    int root[Ts], loc[Ts];
    for (i = 1; i <= 255; i++)
    {
        int q = 1;
        for (j = 1; j <= l[u]; j++)
            if (reg[j] != 0xff)
            {
                reg[j] = (reg[j] + j) % 255;
                q ^= alpha_to[reg[j]];
            }
        if (!q)        /* записываем корень и индекс номера локатора ошибки */
        {
            root[count] = i;
            loc[count] = 255 - i;
            count++;
        }
    }
    if (count != l[u])    /* количество корней != степени elp => >Ts ошибок, решение невозможно */
    {
        for (i = 0; i < 255; i++)
            recd[i] = alpha_to[recd[i]];	/* преобразвать recd[] обратно */
        return 2;
    }

    /* количество корней == степени elp следовательно кол. ошибок <= Ts */

    /* формируем полином z(x) */
    int z[Ts + 1];
    for (i = 1; i <= l[u]; i++)	/* Z[0] = 1 всегда */
    {
        if ((s[i] != 0xff) && (elp[u][i] != -1))
            z[i] = alpha_to[s[i]] ^ alpha_to[elp[u][i]];
        else if ((s[i] != 0xff) && (elp[u][i] == -1))
            z[i] = alpha_to[s[i]];
        else if ((s[i] == 0xff) && (elp[u][i] != -1))
            z[i] = alpha_to[elp[u][i]];
        else
            z[i] = 0;
        for (j = 1; j < i; j++)
            if ((s[j] != 0xff) && (elp[u][i - j] != -1))
                z[i] ^= alpha_to[(elp[u][i - j] + s[j]) % 255];
        z[i] = index_of[z[i]];		/* в индексную форму */
    }

    /*
       4) вычисляем ошибки в позициях loc[i] и исправляем их
    */

    int err[255];
    for (i = 0; i < 255; i++)
    {
        err[i] = 0;
        recd[i] = alpha_to[recd[i]];
    }
    for (i = 0; i < l[u]; i++)	/* сначала вычисляем числитель ошибки */
    {
        err[loc[i]] = 1;			/* accounts for z[0] */
        for (j = 1; j <= l[u]; j++)
            if (z[j] != 0xff)
                err[loc[i]] ^= alpha_to[(z[j] + j * root[i]) % 255];
        if (err[loc[i]] != 0)
        {
            err[loc[i]] = index_of[err[loc[i]]];
            int q = 0;				/* формируем знаменатель */
            for (j = 0; j < l[u]; j++)
                if (j != i)
                    q += index_of[1 ^ alpha_to[(loc[j] + root[i]) % 255]];
            q = q % 255;
            err[loc[i]] = alpha_to[(err[loc[i]] - q + 255) % 255];
            recd[loc[i]] ^= err[loc[i]]; /* исправляем ошибку */
        }
    }
    return 1;
}

ReedSolomonCoding::ReedSolomonCoding(){
    generate_gf();
    gen_poly(Tn, gn);	// compute the generator polynomial for 'NASA'
    gen_poly(Ts, gs);
}
