#ifndef __VALUE_H__
#define __VALUE_H__

#include <chrono>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>

/**
 * @brief Class representing a value stored in the key-value store.
 *
 * This class stores information about a students in the form of a last name,
 * first name, birth year, city, and number of coins. It also supports an
 * optional time-to-live (TTL) parameter, which specifies how long the value
 * should be stored in the key-value store before it is automatically deleted.
 */
class Value {
 public:
  enum TypeValidation { kDate, kCoin, kTTL };
  Value() = default;
  Value(const std::string &last_name, const std::string &first_name,
        const std::string &birth_year, const std::string &city,
        const std::string &coins, std::optional<std::string> ttl = std::nullopt)
      : last_name_(std::move(last_name)),
        first_name_(std::move(first_name)),
        birth_year_(ValidateNumber(birth_year, TypeValidation::kDate)),
        city_(std::move(city)),
        coins_(ValidateNumber(coins, TypeValidation::kCoin)),
        ttl_(ttl ? ValidateNumber(*ttl, TypeValidation::kTTL) : ttl),
        creation_time_(std::chrono::system_clock::now()) {}

  void Update(const std::string &value) {
    std::istringstream ss(value);
    auto [last_name, first_name, birth_year, city, coins, ttl] =
        ParseValueFields(ss);

    if (last_name != "-") last_name_ = last_name;
    if (first_name != "-") first_name_ = first_name;
    if (birth_year != "-") birth_year_ = ValidateNumber(birth_year, kDate);
    if (city != "-") city_ = city;
    if (coins != "-") coins_ = ValidateNumber(coins, TypeValidation::kCoin);
    if (ttl.has_value() && ttl.value() != "-")
      ttl_ = ValidateNumber(*ttl, TypeValidation::kTTL);
  }

  std::optional<std::size_t> TTL() const {
    if (!ttl_.has_value()) {
      return std::nullopt;
    }
    auto elapsed_seconds = CalculateElapsedTime();
    auto ttl_seconds = std::stoull(ttl_.value());
    if (elapsed_seconds >= ttl_seconds) {
      return 0u;
    } else {
      return ttl_seconds - elapsed_seconds;
    }
  }

  bool IsExpired() const {
    if (!ttl_.has_value()) {
      return false;
    }
    auto elapsed_seconds = CalculateElapsedTime();
    return elapsed_seconds >= std::stoull(ttl_.value());
  }

  std::string ToQuotedString() const {
    std::stringstream ss;
    ss << std::quoted(last_name_) << " " << std::quoted(first_name_) << " "
       << birth_year_ << " " << std::quoted(city_) << " " << coins_;
    return ss.str();
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << last_name_ << " " << first_name_ << " " << birth_year_ << " " << city_
       << " " << coins_;
    return ss.str();
  }

  static Value FromString(std::string value) {
    std::istringstream ss(value);
    std::string last_name, first_name, birth_year, city, coins;
    ss >> std::quoted(last_name) >> std::quoted(first_name) >> birth_year >>
        std::quoted(city) >> coins;
    return Value(last_name, first_name, birth_year, city, coins);
  }

  bool Match(const std::string &value) const {
    std::istringstream ss(value);
    auto [last_name, first_name, birth_year, city, coins, ttl] =
        ParseValueFields(ss);
    return (last_name == "-" || last_name == last_name_) &&
           (first_name == "-" || first_name == first_name_) &&
           (birth_year == "-" ||
            ValidateNumber(birth_year, kDate) == birth_year_) &&
           (city == "-" || city == city_) &&
           (coins == "-" || ValidateNumber(coins, kCoin) == coins_);
  }

  bool operator==(const Value &other) const {
    return (last_name_ == other.last_name_) &&
           (first_name_ == other.first_name_) &&
           (birth_year_ == other.birth_year_) && (city_ == other.city_) &&
           (coins_ == other.coins_);
  }

 private:
  std::size_t CalculateElapsedTime() const {
    auto now = std::chrono::system_clock::now();
    auto elapsed_seconds =
        std::chrono::duration_cast<std::chrono::seconds>(now - creation_time_);
    return elapsed_seconds.count();
  }

  static std::string ValidateNumber(const std::string &input,
                                    const TypeValidation &type) {
    try {
      auto value = std::stoi(input);
      if (type == TypeValidation::kDate &&
          (std::to_string(value).length() != 4 || value < 0)) {
        throw input;
      } else if (type == TypeValidation::kCoin && value < 0) {
        throw input;
      } else if (type == TypeValidation::kTTL && value < 0) {
        throw input;
      }
      return std::to_string(value);
    } catch (const std::exception &e) {
      throw std::invalid_argument("ERROR: unable to cast value \"" + input +
                                  "\" to type int");
    } catch (...) {
      throw std::invalid_argument("ERROR: invalid input format for value \"" +
                                  input + "\"");
    }
  }

  static std::tuple<std::string, std::string, std::string, std::string,
                    std::string, std::optional<std::string>>
  ParseValueFields(std::istringstream &ss) {
    std::string last_name, first_name, birth_year, city, coins, ttl;
    std::optional<std::string> ttl_val;

    if (!(ss >> last_name >> first_name >> birth_year >> city >> coins)) {
      throw std::invalid_argument("Invalid input format");
    }

    if (!ss.eof()) {
      ss >> ttl;
      if (!ss.eof()) {
        throw std::invalid_argument("Too many arguments");
      }
      ttl_val = ttl;
    }

    return std::make_tuple(last_name, first_name, birth_year, city, coins,
                           ttl_val);
  }

  std::string last_name_;
  std::string first_name_;
  std::string birth_year_;
  std::string city_;
  std::string coins_;
  std::optional<std::string> ttl_;
  std::chrono::time_point<std::chrono::system_clock> creation_time_;
};

#endif  // __VALUE_H__