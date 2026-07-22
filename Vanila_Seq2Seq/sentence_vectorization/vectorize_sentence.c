#include "include.h"

void vectorize_sentence(const wchar_t *sentence, int **sentence_vector, const wchar_t **vocab_array, const int vocab_size)
{
   if (sentence == NULL || sentence_vector == NULL || vocab_array == NULL || vocab_size <= 0)
    {
        return;
    }

    *sentence_vector = malloc(MAX_SENTENCE_LENGTH * sizeof(int));
    if (*sentence_vector != NULL)
    {
        (*sentence_vector)[0] = SOS_ID;

        wchar_t curr_buffer[MAX_TOKEN_LENGTH];
        int curr_id, prev_id;
        int i = 0, vec_i = 1;
        
        while (vec_i < MAX_SENTENCE_LENGTH)
        {
            if (sentence[i] == L'\0')
            {
                while (vec_i < MAX_SENTENCE_LENGTH - 1)
                {
                    (*sentence_vector)[vec_i] = PAD_ID;
                    vec_i += 1;
                }
                (*sentence_vector)[vec_i] = EOS_ID;
                return;
            } else if (sentence[i] == L' ')
            {
                (*sentence_vector)[vec_i] = SPC_ID;
                vec_i += 1;
                i += 1;
            }else
            {
                int j = 0;
                curr_id = -1;
                prev_id = -1;
                while ((j < MAX_TOKEN_LENGTH - 1) && (sentence[i + j] != L'\0') && (vec_i < MAX_SENTENCE_LENGTH))
                {
                    wcsncpy(curr_buffer, &(sentence[i]), j + 1);
                    curr_buffer[j + 1] = L'\0';
                    curr_id = vocab_get_id((const wchar_t *) curr_buffer, vocab_array, vocab_size, UNK_ID);
                    if (curr_id == UNK_ID)
                    {
                        if (prev_id == -1)
                        {
                            (*sentence_vector)[vec_i] = UNK_ID;
                            vec_i += 1;
                            i += 1;
                            break;
                        } else
                        {
                            (*sentence_vector)[vec_i] = prev_id;
                            vec_i += 1;
                            i += j;
                            curr_id = -1;
                            prev_id = -1;
                            break;
                        }
                    } else
                    {
                        prev_id = curr_id;
                        j += 1;
                    }
                }
                if ((curr_id != UNK_ID) && (prev_id != -1) && (vec_i < MAX_SENTENCE_LENGTH))
                {
                    (*sentence_vector)[vec_i] = prev_id;
                    vec_i += 1;
                    i += j;
                }
            }
        }
    }
}
