#include <m_pd.h>

#include "adc/mcp3424.hpp"

// #define TEST

#ifdef __cplusplus
extern "C" {
#endif

static t_class* intraconnection_adc_class = NULL;

typedef struct _intraconnection_adc
{
    t_object x_obj;
    mcp3424 adc1{0x68};
    mcp3424 adc2{0x69};
    t_atom values[8];
} t_intraconnection_adc;


void 
intraconnection_adc_bang(t_intraconnection_adc* x) 
{
    logpost(x, 3, "Reading adcs!\n");
    #if defined(TEST)
    for (int i = 0; i < 8; i++){
        SETFLOAT(x->values + i, (t_float) i/0.9f);
    }
    #else
    uint8_t idx = 0;
    if (x->adc1.read()) {
        for (int i = 0; i < 4; i++){
            int32_t v = x->adc1.get(i);
            logpost(x, 4, "Raw value: %ld", v);
	    if (v != 0xfefefefe) {
                float v_float = v;
                logpost(x, 4, "Setting value %d: %f", idx, v_float);
                SETFLOAT(x->values + idx, (t_float) v_float);
		idx++;
            }
        }
    }

    if (idx == 0)
        idx += 4;

    if (x->adc2.read()) {
        for (int i = 0; i < 4; i++){
            int32_t v = x->adc2.get(i);
            if (v != 0xfefefefe) {
                float v_float = v;
                logpost(x, 4, "Setting value %d(%d): %f", idx, i, v_float);
                SETFLOAT(x->values + idx, (t_float) v_float);
		idx++;
            }
        }
    }
    #endif

    outlet_list(x->x_obj.ob_outlet, &s_list, 8, x->values);
}  

void*
intraconnection_adc_new(void) 
{
    t_intraconnection_adc *x = (t_intraconnection_adc *)pd_new(intraconnection_adc_class);
    outlet_new(&x->x_obj, &s_list);

    return (void *)x;
}

void 
intraconnection_adc_setup(void) 
{
    intraconnection_adc_class = class_new(gensym("intraconnection_adc"),
        (t_newmethod)intraconnection_adc_new, NULL,
        sizeof(t_intraconnection_adc), CLASS_DEFAULT, A_NULL);
    class_addbang(intraconnection_adc_class, intraconnection_adc_bang);
}

#ifdef __cplusplus
}
#endif
