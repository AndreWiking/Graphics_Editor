#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <iostream>
#include <SFML/System/Vector2.hpp>

template<typename T>
class Vector2{
public:
    T X, Y;

    Vector2 () : X(0), Y(0) {}

    constexpr Vector2(T x, T y) : X(x), Y(y) {}

    Vector2& operator=(const Vector2 &vec){
        X = vec.X;
        Y = vec.Y;
        return *this;
    }
    Vector2& operator += (const Vector2 &vec){
        X += vec.X;
        Y += vec.Y;
        return *this;
    }

    Vector2& operator -= (Vector2 vec){
        X -= vec.X;
        Y -= vec.Y;
        return *this;
    }
    Vector2& operator *= (T val){
        X *= val;
        Y *= val;
        return *this;
    }

    Vector2 operator + (Vector2 vec){
        vec += *this;
        return vec;
    }
    Vector2 operator - (const Vector2 &vec){
        return Vector2(X - vec.X, Y - vec.Y);
    }

    Vector2 operator * (T val){
        Vector2 vec = *this;
        return vec *= val;
    }
    T operator * (Vector2 vec){
        return X * vec.Y - vec.X * Y;
    }
    T operator % (Vector2 vec){
        return X * vec.X + Y * vec.Y;
    }

    operator sf::Vector2f() const {
        return sf::Vector2f(static_cast<float>(X), static_cast<float>(Y));
    }
    operator sf::Vector2i () const {
        return sf::Vector2i(static_cast<int>(round(X)), static_cast<int>(round(Y)));
    }
    operator Vector2<double>() const {
        return Vector2<double>(static_cast<double>(X), static_cast<double>(Y));
    }

    bool isZero(){
        return abs(X) < delta && abs(Y) < delta;
    }
    T Length(){
        return sqrt(X * X + Y * Y );
    }
    T SquareLength(){
        return X * X + Y * Y;
    }
    Vector2 Normalized(){
        if ((*this).isZero()) return Vector2();

        double len = (*this).Length();
        return Vector2(X / len, Y / len);
    }
    Vector2 Rotate(T angle){
        return Vector2(X * cos(angle) - Y * sin(angle), X * sin(angle) + Y * cos(angle));
    }

    Vector2 GetNormal(){
        return Vector2(Y, -X);
    }

    Vector2 Project(Vector2 axis){
        return axis * ((*this % axis) / axis.Length() / axis.Length());
    }

    Vector2 Abs(){
        return Vector2(abs(X), abs(Y));
    }

    void Print(){
        std::cout << "(" << X << ", " << Y << ")\n";
    }
    static constexpr double delta = 1e-13;
private:
};

typedef Vector2<double> Vector2F;
typedef Vector2<int> Vector2I;

#endif