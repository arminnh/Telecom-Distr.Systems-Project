#ifndef CLICK_RSVP_HH
#define CLICK_RSVP_HH

#include <click/element.hh>

CLICK_DECLS

#define RSVP_MSG_PATH		    1
#define RSVP_MSG_RESV		    2
#define RSVP_MSG_PATHERR		3
#define RSVP_MSG_RESVERR		4
#define RSVP_MSG_PATHTEAR		5
#define RSVP_MSG_RESVTEAR		6
#define RSVP_MSG_RESVCONF		7


#define RSVP_CLASS_NULL                 0
#define RSVP_CLASS_SESSION              1
#define RSVP_CLASS_RSVP_HOP             3
#define RSVP_CLASS_INTEGRITY            4
#define RSVP_CLASS_TIME_VALUES          5
#define RSVP_CLASS_ERROR_SPEC           6
#define RSVP_CLASS_STYLE                8
#define RSVP_CLASS_SCOPE                7
#define RSVP_CLASS_FLOWSPEC             9
#define RSVP_CLASS_FILTER_SPEC          10
#define RSVP_CLASS_SENDER_TEMPLATE      11
#define RSVP_CLASS_SENDER_TSPEC         12
//ADSPEC NIET
#define RSVP_CLASS_ADSPEC               13
#define RSVP_CLASS_POLICY_DATA          14
#define RSVP_CLASS_RESV_CONFIRM         15

struct RSVPCommonHeader {
	// RSVPCommonHeader() : vers(1), flags(0), RSVP_checksum(0), reserved(0) {}
	unsigned    vers : 4;
	unsigned    flags : 4;
	uint8_t     msg_type;
	uint16_t    RSVP_checksum;
	uint8_t     send_TTL;
	uint8_t     reserved;
	uint16_t    RSVP_length;
};

struct RSVPObjectHeader {
	uint16_t length;
	uint8_t class_num;
	uint8_t c_type;
};

struct RSVPSessionClass { // class num = 1, C-type = 1
	in_addr IPv4_dest_address;
	uint8_t protocol_id;
	uint8_t flags;
	uint16_t dst_port;
};

struct RSVPHopClass { // class num = 3, C-type = 1
	in_addr IPv4_next_previous_hop_address;
	uint32_t logical_interface_handle;
};

struct RSVPIntegrityClass { // class num = 4, C-type = 1
	unsigned flags : 4;
	unsigned reserved : 4;
	uint64_t key_identifier : 48;
	uint64_t sequence_number;
	uint64_t keyed_message_digest_1;
	uint64_t keyed_message_digest_2;
};

struct RSVPTimeValuesClass { // class num = 5, C-type = 1
	uint32_t refresh_period_r;
};

struct RSVPErrorSpecClass { // class num = 6, C-type = 1
	in_addr IPv4_error_node_address;
	uint8_t flags;
	uint8_t error_code;
	uint16_t error_value;
};

// scope class: class num = 7, C-type = 1
// array of in_addrs

struct RSVPStyleClass { // class num = 8, C-type = 1
	uint8_t flags;
	uint32_t option_vector : 24;
};

struct RSVPFlowspecClass { // class num = 9
	// RFC2210
};

struct RSVPFilterSpecClass { // class num = 10, C-type = 1
	in_addr src_address;
	uint16_t nothing;
	uint16_t src_port;
};

typedef RSVPFilterSpecClass RSVPSenderTemplateClass; // class num = 11, C-type = 1

// RSVPSenderTSpecClass class num = 12, C-type = 2
// RSVPPolicyData class num = 14, C-type = 1

struct RSVPResvConfirmClass { // class num = 15, C-type = 1
	in_addr receiver_address;
};

size_t sizeofRSVPClass(uint16_t class_num, uint16_t c_type);

void initRSVPCommonHeader(RSVPCommonHeader*, uint8_t msg_type, uint8_t send_TTL);
void initRSVPObjectHeader(RSVPObjectHeader*, uint8_t class_num, uint8_t c_type);

CLICK_ENDDECLS

#endif