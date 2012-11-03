#ifndef __SNIS_MARSHAL_C__
#define __SNIS_MARSHAL_C__

#pragma pack(1)
struct packed_double 
{
	int64_t fractional;
	int32_t exponent;
};
#pragma pack()

struct packed_buffer
{
	unsigned char *buffer;
	uint16_t buffer_size; /* size of space allocated for buffer */
	int buffer_cursor;
};

struct packed_buffer_queue_entry {
	struct packed_buffer *buffer;
	struct packed_buffer_queue_entry *next;
};

struct packed_buffer_queue {
	struct packed_buffer_queue_entry *head, *tail;
};

#ifdef DEFINE_SNIS_MARSHAL_GLOBALS
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL struct packed_buffer * packed_buffer_allocate(int size); 
GLOBAL void packed_buffer_free(struct packed_buffer *pb);
GLOBAL int packed_buffer_append_double(struct packed_buffer *pb, double value);
GLOBAL int packed_buffer_append_u16(struct packed_buffer *pb, uint16_t value);
GLOBAL int packed_buffer_append_u32(struct packed_buffer *pb, uint32_t value);
GLOBAL uint16_t packed_buffer_extract_u16(struct packed_buffer *pb);
GLOBAL uint32_t packed_buffer_extract_u32(struct packed_buffer *pb);
GLOBAL double packed_buffer_extract_double(struct packed_buffer *pb);
GLOBAL int packed_buffer_append_string(struct packed_buffer *pb, unsigned char *str, unsigned short len);
GLOBAL int packed_buffer_extract_string(struct packed_buffer *pb, char *buffer, int buflen);
GLOBAL struct packed_buffer *packed_buffer_queue_combine(struct packed_buffer_queue *pbqh, pthread_mutex_t *mutex);
GLOBAL void packed_buffer_queue_add(struct packed_buffer_queue *pbqh, struct packed_buffer *pb,
                pthread_mutex_t *mutex);
GLOBAL void packed_buffer_queue_init(struct packed_buffer_queue *pbq);
GLOBAL void packed_buffer_queue_print(struct packed_buffer_queue *pbg);

#undef GLOBAL
#endif

