#pragma once

#include "duckdb/common/vector.hpp"
#include "duckpgq/parser/path_pattern.hpp"
#include "duckdb/parser/tableref.hpp"
#include "duckdb/common/enums/expression_type.hpp"

namespace duckdb {

class MatchExpression : public ParsedExpression {
public:
	static constexpr const ExpressionClass TYPE = ExpressionClass::FUNCTION;

public:
	MatchExpression() : ParsedExpression(ExpressionType::FUNCTION_REF, ExpressionClass::FUNCTION) {
	}

	string pg_name;
	string alias;
	vector<unique_ptr<PathPattern>> path_patterns;

	vector<unique_ptr<ParsedExpression>> column_list;

	unique_ptr<ParsedExpression> where_clause;

public:
	string ToString() const override;
	bool Equals(const BaseExpression &other_p) const override;

	unique_ptr<ParsedExpression> Copy() const override;

	//! Serializes a blob into a MatchRef
	void Serialize(Serializer &serializer) const override;
	//! Deserializes a blob back into a MatchRef
	static unique_ptr<ParsedExpression> Deserialize(Deserializer &deserializer);
};

} // namespace duckdb
