#include "drivers/encoder-pio/encoder.hpp"
#include <cstdio>
#include <cfloat>

#define MP_OBJ_TO_PTR2(o, t) ((t *)(uintptr_t)(o))

using namespace pimoroni;
//using namespace encoder;

extern "C" {
#include "encoder.h"
#include "py/builtin.h"


/********** Snapshot **********/

/***** Variables Struct *****/
typedef struct _Snapshot_obj_t {
    mp_obj_base_t base;
    Encoder::Snapshot *snapshot;
} _Snapshot_obj_t;


/***** Print *****/
void Snapshot_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    (void)kind; //Unused input parameter
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    Encoder::Snapshot* snap = self->snapshot;
    mp_print_str(print, "Snapshot(count = ");
    mp_obj_print_helper(print, mp_obj_new_int(snap->count), PRINT_REPR);
    mp_print_str(print, ", delta = ");
    mp_obj_print_helper(print, mp_obj_new_int(snap->delta), PRINT_REPR);
    mp_print_str(print, ", freq = ");
    mp_obj_print_helper(print, mp_obj_new_float(snap->frequency), PRINT_REPR);
    mp_print_str(print, ")");
}


/***** Constructor *****/
mp_obj_t Snapshot_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    mp_raise_TypeError("cannot create an instance of Snapshot. They can only be created by calling take_snapshot on an Encoder object");
    return mp_const_none;
}


/***** Destructor ******/
mp_obj_t Snapshot___del__(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    delete self->snapshot;
    return mp_const_none;
}


/***** Methods *****/
mp_obj_t Snapshot_count(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    return mp_obj_new_int(self->snapshot->count);
}

mp_obj_t Snapshot_delta(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    return mp_obj_new_int(self->snapshot->delta);
}

mp_obj_t Snapshot_frequency(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    return mp_obj_new_float(self->snapshot->frequency);
}

mp_obj_t Snapshot_revolutions(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    return mp_obj_new_int(self->snapshot->revolutions());
}

mp_obj_t Snapshot_degrees(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    return mp_obj_new_int(self->snapshot->degrees());
}

mp_obj_t Snapshot_radians(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    return mp_obj_new_int(self->snapshot->radians());
}

mp_obj_t Snapshot_revolutions_delta(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    return mp_obj_new_int(self->snapshot->revolutions_delta());
}

mp_obj_t Snapshot_degrees_delta(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    return mp_obj_new_int(self->snapshot->degrees_delta());
}

mp_obj_t Snapshot_radians_delta(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    return mp_obj_new_int(self->snapshot->radians_delta());
}

mp_obj_t Snapshot_revolutions_per_second(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    return mp_obj_new_float(self->snapshot->revolutions_per_second());
}

mp_obj_t Snapshot_revolutions_per_minute(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    return mp_obj_new_float(self->snapshot->revolutions_per_minute());
}

mp_obj_t Snapshot_degrees_per_second(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    return mp_obj_new_float(self->snapshot->degrees_per_second());
}

mp_obj_t Snapshot_radians_per_second(mp_obj_t self_in) {
    _Snapshot_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Snapshot_obj_t);
    return mp_obj_new_float(self->snapshot->radians_per_second());
}


/********** Encoder **********/

/***** Variables Struct *****/
typedef struct _Encoder_obj_t {
    mp_obj_base_t base;
    Encoder* encoder;
} _Encoder_obj_t;


/***** Print *****/
void Encoder_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    (void)kind; //Unused input parameter
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);
    mp_print_str(print, "Encoder(");

    mp_print_str(print, "pins = (");
    pin_pair pins = self->encoder->pins();
    mp_obj_print_helper(print, mp_obj_new_int(pins.a), PRINT_REPR);
    mp_print_str(print, ", ");
    mp_obj_print_helper(print, mp_obj_new_int(pins.b), PRINT_REPR);
    mp_print_str(print, ", ");
    mp_obj_print_helper(print, mp_obj_new_int(self->encoder->common_pin()), PRINT_REPR);
    mp_print_str(print, ")");

    if(self->encoder->direction() == NORMAL)
        mp_print_str(print, ", direction = NORMAL");
    else
        mp_print_str(print, ", direction = REVERSED");

    mp_print_str(print, ", counts_per_rev = ");
    mp_obj_print_helper(print, mp_obj_new_float(self->encoder->counts_per_revolution()), PRINT_REPR);
    mp_print_str(print, ")");
}


/***** Constructor *****/
mp_obj_t Encoder_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    _Encoder_obj_t *self = nullptr;

    enum { ARG_pio, ARG_sm, ARG_pins, ARG_common_pin, ARG_count_microsteps, ARG_freq_divider };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_pio, MP_ARG_REQUIRED | MP_ARG_INT },
        { MP_QSTR_sm, MP_ARG_REQUIRED | MP_ARG_INT },
        { MP_QSTR_pins, MP_ARG_REQUIRED | MP_ARG_OBJ },
        { MP_QSTR_common_pin, MP_ARG_INT, {.u_int = PIN_UNUSED} },
        { MP_QSTR_count_microsteps, MP_ARG_BOOL, {.u_bool = false} },
        { MP_QSTR_freq_divider, MP_ARG_OBJ, {.u_obj = mp_const_none} },
    };

    // Parse args.
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, all_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    PIO pio = args[ARG_pio].u_int == 0 ? pio0 : pio1;
    int sm = args[ARG_sm].u_int;

    size_t pin_count = 0;
    pin_pair pins;

    // Determine what pair of pins this encoder will use
    const mp_obj_t object = args[ARG_pins].u_obj;
    mp_obj_t *items = nullptr;
    if(mp_obj_is_type(object, &mp_type_list)) {
        mp_obj_list_t *list = MP_OBJ_TO_PTR2(object, mp_obj_list_t);
        pin_count = list->len;
        items = list->items;
    }
    else if(mp_obj_is_type(object, &mp_type_tuple)) {
        mp_obj_tuple_t *tuple = MP_OBJ_TO_PTR2(object, mp_obj_tuple_t);
        pin_count = tuple->len;
        items = tuple->items;
    }

    if(items == nullptr)
        mp_raise_TypeError("cannot convert object to a list or tuple of pins");
    else if(pin_count != 2)
        mp_raise_TypeError("list or tuple must only contain two integers");
    else {
        int a = mp_obj_get_int(items[0]);
        int b = mp_obj_get_int(items[1]);
        if((a < 0 || a >= (int)NUM_BANK0_GPIOS) ||
           (b < 0 || b >= (int)NUM_BANK0_GPIOS)) {
            mp_raise_ValueError("a pin in the list or tuple is out of range. Expected 0 to 29");
        }
        else if(a == b) {
            mp_raise_ValueError("cannot use the same pin for encoder A and B");
        }

        pins.a = (uint8_t)a;
        pins.b = (uint8_t)b;
    }

    float freq_divider = Encoder::DEFAULT_FREQ_DIVIDER;
    if(args[ARG_freq_divider].u_obj != mp_const_none) {
        freq_divider = mp_obj_get_float(args[ARG_freq_divider].u_obj);
    }

    bool count_microsteps = args[ARG_count_microsteps].u_bool;

    Encoder *encoder = new Encoder(pio, sm, pins, args[ARG_common_pin].u_int, NORMAL, Encoder::DEFAULT_COUNTS_PER_REV, count_microsteps, freq_divider);
    if(!encoder->init()) {
        delete encoder;
        mp_raise_msg(&mp_type_RuntimeError, "unable to allocate the hardware resources needed to initialise this Encoder. Try running `import gc` followed by `gc.collect()` before creating it");
    }

    self = m_new_obj_with_finaliser(_Encoder_obj_t);
    self->base.type = &Encoder_type;
    self->encoder = encoder;

    return MP_OBJ_FROM_PTR(self);
}


/***** Destructor ******/
mp_obj_t Encoder___del__(mp_obj_t self_in) {
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);
    delete self->encoder;
    return mp_const_none;
}


/***** Methods *****/
extern mp_obj_t Encoder_pins(mp_obj_t self_in) {
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);
    pin_pair pins = self->encoder->pins();

    mp_obj_t tuple[2];
    tuple[0] = mp_obj_new_int(pins.a);
    tuple[1] = mp_obj_new_int(pins.b);
    return mp_obj_new_tuple(2, tuple);
}

extern mp_obj_t Encoder_common_pin(mp_obj_t self_in) {
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);
    return mp_obj_new_int(self->encoder->common_pin());
}


extern mp_obj_t Encoder_state(mp_obj_t self_in) {
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);
    bool_pair state = self->encoder->state();

    mp_obj_t tuple[2];
    tuple[0] = state.a ? mp_const_true : mp_const_false;
    tuple[1] = state.b ? mp_const_true : mp_const_false;
    return mp_obj_new_tuple(2, tuple);
}

extern mp_obj_t Encoder_count(mp_obj_t self_in) {
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);
    return mp_obj_new_int(self->encoder->count());
}

extern mp_obj_t Encoder_delta(mp_obj_t self_in) {
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);
    return mp_obj_new_int(self->encoder->delta());
}

extern mp_obj_t Encoder_zero(mp_obj_t self_in) {
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);
    self->encoder->zero();
    return mp_const_none;
}

extern mp_obj_t Encoder_step(mp_obj_t self_in) {
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);
    return mp_obj_new_int(self->encoder->step());
}

extern mp_obj_t Encoder_turn(mp_obj_t self_in) {
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);
    return mp_obj_new_int(self->encoder->turn());
}

extern mp_obj_t Encoder_revolutions(mp_obj_t self_in) {
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);
    return mp_obj_new_float(self->encoder->revolutions());
}

extern mp_obj_t Encoder_degrees(mp_obj_t self_in) {
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);
    return mp_obj_new_float(self->encoder->degrees());
}

extern mp_obj_t Encoder_radians(mp_obj_t self_in) {
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);
    return mp_obj_new_float(self->encoder->radians());
}

extern mp_obj_t Encoder_direction(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    if(n_args <= 1) {
        enum { ARG_self };
        static const mp_arg_t allowed_args[] = {
            { MP_QSTR_, MP_ARG_REQUIRED | MP_ARG_OBJ },
        };

        // Parse args.
        mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
        mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

        _Encoder_obj_t *self = MP_OBJ_TO_PTR2(args[ARG_self].u_obj, _Encoder_obj_t);

        return mp_obj_new_int(self->encoder->direction());
    }
    else {
        enum { ARG_self, ARG_direction };
        static const mp_arg_t allowed_args[] = {
            { MP_QSTR_, MP_ARG_REQUIRED | MP_ARG_OBJ },
            { MP_QSTR_direction, MP_ARG_REQUIRED | MP_ARG_INT },
        };

        // Parse args.
        mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
        mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

        _Encoder_obj_t *self = MP_OBJ_TO_PTR2(args[ARG_self].u_obj, _Encoder_obj_t);

        int direction = args[ARG_direction].u_int;
        if(direction < 0 || direction > 1) {
            mp_raise_ValueError("direction out of range. Expected NORMAL (0) or REVERSED (1)");
        }
        self->encoder->direction((Direction)direction);
        return mp_const_none;
    }
}

extern mp_obj_t Encoder_counts_per_revolution(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    if(n_args <= 1) {
        enum { ARG_self };
        static const mp_arg_t allowed_args[] = {
            { MP_QSTR_, MP_ARG_REQUIRED | MP_ARG_OBJ },
        };

        // Parse args.
        mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
        mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

        _Encoder_obj_t *self = MP_OBJ_TO_PTR2(args[ARG_self].u_obj, _Encoder_obj_t);

        return mp_obj_new_float(self->encoder->counts_per_revolution());
    }
    else {
        enum { ARG_self, ARG_counts_per_rev };
        static const mp_arg_t allowed_args[] = {
            { MP_QSTR_, MP_ARG_REQUIRED | MP_ARG_OBJ },
            { MP_QSTR_counts_per_rev, MP_ARG_REQUIRED | MP_ARG_OBJ },
        };

        // Parse args.
        mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
        mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

        _Encoder_obj_t *self = MP_OBJ_TO_PTR2(args[ARG_self].u_obj, _Encoder_obj_t);

        float counts_per_rev = mp_obj_get_float(args[ARG_counts_per_rev].u_obj);
        if(counts_per_rev < FLT_EPSILON) {
            mp_raise_ValueError("counts_per_rev out of range. Expected greater than 0.0");
        }
        self->encoder->counts_per_revolution(counts_per_rev);
        return mp_const_none;
    }
}

extern mp_obj_t Encoder_take_snapshot(mp_obj_t self_in) {
    _Encoder_obj_t *self = MP_OBJ_TO_PTR2(self_in, _Encoder_obj_t);

    // Create a new MP Snapshot instance and assign a copy of the encoder's snapshot to it
    _Snapshot_obj_t *snap = m_new_obj_with_finaliser(_Snapshot_obj_t);
    snap->base.type = &Snapshot_type;

    snap->snapshot = new Encoder::Snapshot(self->encoder->take_snapshot());
    return MP_OBJ_FROM_PTR(snap);
}
}
