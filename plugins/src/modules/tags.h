#ifndef TAGS_H_INCLUDED
#define TAGS_H_INCLUDED

#include "sdk/amx/amx.h"
#include <string>

typedef const struct tag_info *tag_ptr;

class tag_operations
{
protected:
	tag_operations() = default;
public:
	virtual cell add(tag_ptr tag, cell a, cell b) const = 0;
	virtual cell sub(tag_ptr tag, cell a, cell b) const = 0;
	virtual cell mul(tag_ptr tag, cell a, cell b) const = 0;
	virtual cell div(tag_ptr tag, cell a, cell b) const = 0;
	virtual cell mod(tag_ptr tag, cell a, cell b) const = 0;
	virtual cell neg(tag_ptr tag, cell a) const = 0;
	virtual bool eq(tag_ptr tag, cell a, cell b) const = 0;
	virtual bool eq(tag_ptr tag, const cell *a, const cell *b, cell size) const = 0;
	virtual bool neq(tag_ptr tag, cell a, cell b) const = 0;
	virtual bool neq(tag_ptr tag, const cell *a, const cell *b, cell size) const = 0;
	virtual bool lt(tag_ptr tag, cell a, cell b) const = 0;
	virtual bool gt(tag_ptr tag, cell a, cell b) const = 0;
	virtual bool lte(tag_ptr tag, cell a, cell b) const = 0;
	virtual bool gte(tag_ptr tag, cell a, cell b) const = 0;
	virtual bool not(tag_ptr tag, cell a) const = 0;

	virtual std::basic_string<cell> to_string(tag_ptr tag, cell arg) const = 0;
	virtual std::basic_string<cell> to_string(tag_ptr tag, const cell *arg, cell size) const = 0;
	virtual void append_string(tag_ptr tag, cell arg, std::basic_string<cell> &str) const = 0;
	virtual char format_spec(tag_ptr tag, bool arr) const = 0;
	virtual bool del(tag_ptr tag, cell arg) const = 0;
	virtual bool free(tag_ptr tag, cell arg) const = 0;
	virtual bool collect(tag_ptr tag, const cell *arg, cell size) const = 0;
	virtual cell copy(tag_ptr tag, cell arg) const = 0;
	virtual cell clone(tag_ptr tag, cell arg) const = 0;
	virtual size_t hash(tag_ptr tag, cell arg) const = 0;
	virtual ~tag_operations() = default;
};

enum class op_type
{
	add = 1,
	sub = 2,
	mul = 3,
	div = 4,
	mod = 5,
	neg = 6,
	inc = 7,
	dec = 8,

	eq = 10,
	neq = 11,
	lt = 12,
	gt = 13,
	lte = 14,
	gte = 15,
	not = 16,

	string = 20,
	del = 21,
	free = 22,
	collect = 23,
	copy = 24,
	clone = 25,
	hash = 26,
};

class tag_control
{
protected:
	tag_control() = default;
public:
	virtual bool set_op(op_type type, AMX *amx, const char *handler, const char *add_format, const cell *args, int numargs) = 0;
	virtual bool lock() = 0;
	virtual ~tag_control() = default;
};

struct tag_info
{
	cell uid;
	std::string name;
	tag_ptr base;

	tag_info(cell uid, std::string &&name, tag_ptr base);

	bool strong() const;
	bool inherits_from(cell parent) const;
	bool inherits_from(tag_ptr parent) const;
	tag_ptr find_top_base() const;
	bool same_base(tag_ptr tag) const;
	cell get_id(AMX *amx) const;
	cell call_op(tag_ptr tag, op_type type, cell a, cell b) const;
	const tag_operations &get_ops() const;
	tag_control *get_control() const;
};

namespace tags
{
	constexpr const cell tag_unknown = 0;
	constexpr const cell tag_cell = 1;
	constexpr const cell tag_bool = 2;
	constexpr const cell tag_char = 3;
	constexpr const cell tag_float = 4;
	constexpr const cell tag_string = 5;
	constexpr const cell tag_variant = 6;
	constexpr const cell tag_list = 7;
	constexpr const cell tag_map = 8;
	constexpr const cell tag_iter = 9;
	constexpr const cell tag_ref = 10;
	constexpr const cell tag_task = 11;

	tag_ptr find_tag(const char *name, size_t sublen=-1);
	tag_ptr find_tag(AMX *amx, cell tag_id);
	tag_ptr find_tag(cell tag_uid);
	tag_ptr find_existing_tag(const char *name, size_t sublen = -1);
	tag_ptr new_tag(const char *name, cell base_id);
}

#endif
