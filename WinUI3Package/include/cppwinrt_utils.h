#pragma once


#define DEFINE_PROPERTY(type, name)                                      \
public:                                                                  \
                                                                         \
    type name() const                                                    \
    {                                                                    \
        return _##name;                                                  \
    }                                                                    \
    void name(const type& value)                                         \
    {                                                                    \
       if (_##name != value){                                            \
          _##name = value;                                               \
       }                                                                 \
    }                                                                    \
                                                                         \
private:                                                                 \
    type _##name;


#define DEFINE_PROPERTY2(type, name)                                      \
public:                                                                  \
                                                                         \
    type name() const                                                    \
    {                                                                    \
        return _##name;                                                  \
    }                                                                    \
    void name(const type& value)                                         \
    {                                                                    \
       if (_##name != value){                                            \
          _##name = value;                                               \
       }                                                                 \
    }                                                                    \
                                                                         \
private:                                                                 \
    type _##name{nullptr};

#define DEPENDENCY_PROPERTY(type, name)                                  \
public:                                                                  \
                                                                         \
    static winrt::Microsoft::UI::Xaml::DependencyProperty name##Property() \
    {                                                                    \
        return _##name##Property;                                        \
    }                                                                    \
                                                                         \
    type name() const                                                    \
    {                                                                    \
        return winrt::unbox_value<type>(GetValue(_##name##Property));    \
    }                                                                    \
                                                                         \
    void name(const type& value)                                         \
    {                                                                    \
         SetValue(_##name##Property, winrt::box_value(value));           \
    }                                                                   \
                                                                         \
private:                                                                 \
    static winrt::Microsoft::UI::Xaml::DependencyProperty _##name##Property;