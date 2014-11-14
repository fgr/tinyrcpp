#ifndef DEMO1_RCP_COMMON_H_
#define DEMO1_RCP_COMMON_H_

enum class service_ids : std::int8_t {
  length
};

template <typename Enumeration>
int as_int(Enumeration const value)
{
    return static_cast<int>(value);
}

#endif // DEMO1_RCP_COMMON_H_

