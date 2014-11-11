#ifndef DEMO1_RCP_COMMON_H_
#define DEMO1_RCP_COMMON_H_

enum class service_ids : std::int8_t {
  length
};

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

#endif // DEMO1_RCP_COMMON_H_

