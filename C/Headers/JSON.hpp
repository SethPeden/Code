#pragma once

#include <iostream>
#include <ostream>

enum Type {
  VALUE = 0,
  ARRAY = 1,
  OBJECT = 2
};

class JSON {
  private:
    Type type;
    unsigned size;
    char *data;
    JSON &get(const char *, unsigned s = 0) {
      unsigned l, q = 0, c = 0, b = 0;
      for (l = 0; l < this->size - s; ++l) {
        if (this->data[s + l] == '\"')
          q = !q;
        else if (this->data[s + l] == '{')
          ++c;
        else if (this->data[s + l] == '}')
          --c;
        else if (this->data[s + l] == '[')
          ++b;
        else if (this->data[s + l] == ']')
          --b;
        if (!q && !c && !b) {
          ++l;
          break;
        }
      }
      if (l < this->size - s && this->data[s + l - 1] == '\"') {
        char *temp = new char[l + 1];
        for (unsigned i = 0; i < l; ++i)
          temp[i] = this->data[s + i];
        temp[l] = '\0';
        return *(new JSON(temp, true));
      }
      return *(new JSON(""));
    }
  public:
    JSON(const char *data = "{}", bool point = false) {
      if (data[0] == '[')
        this->type = ARRAY;
      else if (data[0] == '{')
        this->type = OBJECT;
      else
        this->type = VALUE;
      this->size = 0;
      while(*(data + size)) ++size;
      if (this->type == VALUE) {
        this->data = new char[this->size += 2];
        this->data[0] = '\"';
        for (unsigned i = 0; i < this->size - 2; ++i)
          this->data[i + 1] = data[i];
        this->data[this->size - 1] = '\"';
      } else {
        if (!point) {
          this->data = new char[this->size];
          for (unsigned i = 0; i < this->size; ++i)
            this->data[i] = data[i];
        } else {
          this->data = (char *) data;
        }
      }
    }
    JSON(char *data, bool point = false) {
      if (data[0] == '[')
        this->type = ARRAY;
      else if (data[0] == '{')
        this->type = OBJECT;
      else
        this->type = VALUE;
      this->size = 0;
      while(*(data + size)) ++size;
      if (this->type == VALUE) {
        if (!point) {
          this->data = new char[this->size += 2];
          this->data[0] = '\"';
          for (unsigned i = 0; i < this->size - 2; ++i)
            this->data[i + 1] = data[i];
          this->data[this->size - 1] = '\"';
        } else {
          this->data = data;
        }
      } else {
        if (!point) {
          this->data = new char[this->size];
          for (unsigned i = 0; i < this->size; ++i)
            this->data[i] = data[i];
        } else {
          this->data = (char *) data;
        }
      }
    }
    JSON(const JSON &copy) {
      this->type = copy.type;
      *this = JSON(copy.data);
    }
    ~JSON() {
      delete[] this->data;
    }
    JSON &operator =(const JSON &copy) {
      delete this->data;
      this->type = copy.type;
      this->size = copy.size;
      for (unsigned i = 0; i < this->size; ++i)
        this->data[i] = copy.data[i];
      return *this;
    }
    unsigned hasKey(const char *key) {
      unsigned l = 0;
      while (*(key + l))
        l++;
      unsigned q = 0, c = 0, b = 0;
      for (unsigned i = 0; i < this->size; ++i) {
        if (!strncmp((this->data + i), key, l) && !q && !c && !b) {
          return i + l + 2;
        }
      }
      return 0;
    }
    unsigned hasKey(char *key) {
      return this->hasKey((const char *) key);
    }
    JSON &operator [](const char *key) {
      unsigned s = this->hasKey(key);
      if (s) {
        return this->get(key, s);
      } else {

      }
      return *(new JSON(""));
    }
    // JSON &operator [](char *key) {
    //   return *(this)[(const char *) key];
    // }


    friend std::ostream &operator <<(std::ostream &os, JSON &obj) {
      return os << (obj.data);
    }
};
