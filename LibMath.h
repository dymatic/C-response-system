/*Supplies geometrical functions as well as data sanitization techniques.*/

#include <cstdlib>
#include <math.h>
/**
 * Adds all of the data in the array.
 *@param data - The list of data to add.
 *@param dataLength - the length of the data list
 *@return the added data
 */
double addAll(double data[], int dataLength)
{
    double collector=0.;
    for(int index=0; index<dataLength; index++)
        collector+=data[index];
    return collector;
}

/**
 * Returns the square of the number.
 *@param number - The number to square.
 *@return the squared number.
 */
double square(double number)
{
    return number*number;
}
/**
 * Returns the average of data.
 *@param data - a list of the data
 *@param dataLength - The length of the data
 */
double mean(double data[], int dataLength)
{
    double collector = addAll(data, dataLength);
    return collector/dataLength;
}
/**
 * Returns the standard deviation of the set of data.
 * Heavily ported from LibMath.java - calculateStandardDeviation
 *@param list - The data to get the standard deviation of.
 *@param listLength - The length of the list
 *@return the standard deviation of the list
 */
double stdDev(double list[], int listLength)
{
    if (listLength == 1)
    {
        return list[0];
    }

    double localList[listLength];
    double collector = 0;

    for (int index = 0; index < listLength; index++)
    {
        localList[index] = list[index];
        localList[index] -= mean(list, listLength);
    }

    for (int index = 0; index < listLength; index++)
    {
        collector += square(localList[index]);
    }

    return square(collector /= (listLength - 1));

}
/**
 * Returns the area of a rectangle with the dimmensions specified.
 * Squares should have the same length and width.
 *@param length - The length of one side of the rectangle.
 *@param width - The width of the other side of the rectangle.
 *@return The area of the rectangle.
 */
double rectangularArea(double length, double width)
{
    return length*width;
}
/**
 * Returns the volume of the rectangular prism.
 *@param length - The length of the prism
 *@param width - The width of the prism
 *@param height - The height of the prism
 *@return volume - The volume of the prism.
 */
double rectangularVolume(double length, double width, double height)
{
    return length*width*height;
}
/**
*Returns the area of the triangle.
*@param base - The length of the bottom portion of the triangle.
*@param height - The height of the triangle from base to tip.
*@return the area of the triangle.
*/
double triangularArea(double base, double height)
{
    return .5*base*height;
}
/**
*Finds the base of a triangular pyramid.
*@param base - The length of the base of the triangle
*@param height - The height of the pyramid
*@return the volume of the pyramid
*/
 double pyramidVolumeTri(double base, double height) {
        return ((1 / 3) * base * height);
    }

    /**
     * Returns the missing side of a right triangle. The two sides to use with
     * this method are the hypotenuse and the side of the triangle that is not
     * missing.
     *
     * @param hypotenuse side
     * @param the non-missing leg.
     * @return missingSide
     */
    double pyThagSide(double hypotenuse, double side1) {
        return sqrt(square(hypotenuse) - square(side1));
    }

    /**
     * Finds the length of the hypotenuse when given the length of both of the
     * legs.
     *
     * @param leg A
     * @param leg B
     * @return hypotenuse
     */
     double pyThagHypotenuse(double side1, double side2) {
        return sqrt(square(side1) + square(side2));
    }

    /**
     * Finds the circumference (perimeter) of a circle using the radius. The
     * radius is the length from the side of the circle to the center. To find
     * it using diameter, divide diameter by 2.
     *
     * @param radius of the circle
     * @return the circumference of the circle
     */
     double circumference(double radius) {
        return ((radius * 2) * M_PI);
    }

    /**
     * Returns the area of a circle when given the radius. The radius is the
     * length from the side of the circle to the center. To find it using
     * diameter, divide by 2.
     *
     * @param radius of the circle
     * @return the Area of the circle.
     */
     double circularArea(double radius) {
        return (square(radius) * M_PI);
    }

    /**
     * Finds the volume of the sphere with the specified radius. The volume is
     * how much space the object occupies.
     *
     * @param radius of the sphere
     * @return volume of the sphere.
     */
     double sphericalVolume(double radius) {
        return ((4 / 3) * M_PI * (pow(radius, 3)));
    }

    /**
     * Returns the area of the cylinder with the specified radius and height.
     *
     * @param radius of the cylinder's circles.
     * @param height of the cylinder
     * @return area of the cylinder
     */
   double cylindricalArea(double radius, double height) {
        return (2 * M_PI * radius * height) + (2 * circularArea(radius));
    }

    /**
     * Returns the volume that the cylinder takes up.
     *
     * @param radius of the cylinder's circles.
     * @param height of the cylinder
     * @return The volume of the cylinder.
     */
     double cylindricalVolume(double radius, double height) {
        return M_PI * square(radius) * height;
    }

    /**
     * Returns the area of a cone when give the radius of it's base, the height
     * of the cone, and the height of the cone's slant.
     *
     * @param The base's radius
     * @param The height of the cone
     * @param The height of the cone's slant
     * @return The area of the cone.
     */
     double coneArea(double radius, double height, double slant) {
        return (M_PI * slant * radius) + circularArea(radius);
    }

    double coneVolume(double radius, double height) {
        return (1 / 3) * circularArea(radius) * height;
    }

    /**
     * Returns the density of the object. Density is equal to the mass divided
     * by volume.
     *
     * @param mass of the object
     * @param volume of the object
     * @return density of the object
     */
     double densityOf(double mass, double volume) {
        return mass / volume;
    }

    /**
     * Converts the celcius temperature to fahrenheit
     *
     * @param The temperature in celcius
     * @return The temperature in fahrenheit
     */
   double convertCelciusToFahrenheit(double celcius) {
        return celcius * (9 / 5) + 32;
    }

    /**
     * Converts the fahrenheit temperature to celcius.
     *
     * @param the fahrenheit temperature
     * @return the celcius temperature
     */
  double convertFahrenheitToCelcius(double fahrenheit) {
        return fahrenheit * (5 / 9) - 32;
    }

    /**
     * Converts microseconds into regular seconds.
     *
     * @param microseconds - The time in micros
     * @return the converted time in normal seconds.
     */
     double microToSec(double microseconds) {
        return microseconds / 1000 / 1000;
    }

    /**
     * Converts the regular seconds into microseconds.
     *
     * @param seconds - The amount of time in seconds.
     * @return the time in microseconds
     */
   double secToMicro(double sec) {
        return sec * 1000 * 1000;
    }

