import googlemaps
from datetime import datetime

from googlemaps import convert
from uuid import uuid4 as places_autocomplete_session_token
import geocoder
import csv

from math import radians, cos, sin, asin, sqrt
import os


def haversine(lon1, lat1, lon2, lat2):
    """
    Calculate the great circle distance between two points 
    on the earth (specified in decimal degrees)
    """
    # convert decimal degrees to radians 
    lon1, lat1, lon2, lat2 = map(radians, [lon1, lat1, lon2, lat2])

    # haversine formula 
    dlon = lon2 - lon1 
    dlat = lat2 - lat1 
    a = sin(dlat/2)**2 + cos(lat1) * cos(lat2) * sin(dlon/2)**2
    c = 2 * asin(sqrt(a)) 
    r = 3956 # Radius of earth in kilometers. Use 3956 for miles
    return c * r




PLACES_FIND_FIELDS_BASIC = set([
    "formatted_address", "geometry", "icon", "id", "name",
    "permanently_closed", "photos", "place_id", "plus_code", "scope",
    "types",
])

PLACES_FIND_FIELDS_CONTACT = set(["opening_hours",])

PLACES_FIND_FIELDS_ATMOSPHERE = set(["price_level", "rating"])

PLACES_FIND_FIELDS = (PLACES_FIND_FIELDS_BASIC ^
                      PLACES_FIND_FIELDS_CONTACT ^
                      PLACES_FIND_FIELDS_ATMOSPHERE)

PLACES_DETAIL_FIELDS_BASIC = set([
    "address_component", "adr_address", "alt_id", "formatted_address",
    "geometry", "icon", "id", "name", "permanently_closed", "photo",
    "place_id", "plus_code", "scope", "type", "url", "utc_offset", "vicinity",
])

PLACES_DETAIL_FIELDS_CONTACT = set([
    "formatted_phone_number", "international_phone_number", "opening_hours",
    "website",
])

PLACES_DETAIL_FIELDS_ATMOSPHERE = set(["price_level", "rating", "review",])

PLACES_DETAIL_FIELDS = (PLACES_DETAIL_FIELDS_BASIC ^
                        PLACES_DETAIL_FIELDS_CONTACT ^
                        PLACES_DETAIL_FIELDS_ATMOSPHERE)







def geocode(client, address=None, components=None, bounds=None, region=None,
            language=None):
    """
    Geocoding is the process of converting addresses
    (like ``"1600 Amphitheatre Parkway, Mountain View, CA"``) into geographic
    coordinates (like latitude 37.423021 and longitude -122.083739), which you
    can use to place markers or position the map.
    :param address: The address to geocode.
    :type address: string
    :param components: A component filter for which you wish to obtain a
        geocode, for example: ``{'administrative_area': 'TX','country': 'US'}``
    :type components: dict
    :param bounds: The bounding box of the viewport within which to bias geocode
        results more prominently.
    :type bounds: string or dict with northeast and southwest keys.
    :param region: The region code, specified as a ccTLD ("top-level domain")
        two-character value.
    :type region: string
    :param language: The language in which to return results.
    :type language: string
    :rtype: list of geocoding results.
    """

    params = {}

    if address:
        params["address"] = address

    if components:
        params["components"] = convert.components(components)

    if bounds:
        params["bounds"] = convert.bounds(bounds)

    if region:
        params["region"] = region

    if language:
        params["language"] = language

    return client._request("/maps/api/geocode/json", params).get("results", [])


def reverse_geocode(client, latlng, result_type=None, location_type=None,
                    language=None):
    """
    Reverse geocoding is the process of converting geographic coordinates into a
    human-readable address.
    :param latlng: The latitude/longitude value or place_id for which you wish
        to obtain the closest, human-readable address.
    :type latlng: string, dict, list, or tuple
    :param result_type: One or more address types to restrict results to.
    :type result_type: string or list of strings
    :param location_type: One or more location types to restrict results to.
    :type location_type: list of strings
    :param language: The language in which to return results.
    :type language: string
    :rtype: list of reverse geocoding results.
    """

    # Check if latlng param is a place_id string.
    #  place_id strings do not contain commas; latlng strings do.
    if convert.is_string(latlng) and ',' not in latlng:
        params = {"place_id": latlng}
    else:
        params = {"latlng": convert.latlng(latlng)}

    if result_type:
        params["result_type"] = convert.join_list("|", result_type)

    if location_type:
        params["location_type"] = convert.join_list("|", location_type)

    if language:
        params["language"] = language

    return client._request("/maps/api/geocode/json", params).get("results", [])



def _places(client, url_part, query=None, location=None, radius=None,
            keyword=None, language=None, min_price=0, max_price=4, name=None,
            open_now=False, rank_by=None, type=None, region=None, page_token=None):
    """
    Internal handler for ``places``, ``places_nearby``, and ``places_radar``.
    See each method's docs for arg details.
    """

    params = {"minprice": min_price, "maxprice": max_price}

    if query:
        params["query"] = query
    if location:
        params["location"] = convert.latlng(location)
    if radius:
        params["radius"] = radius
    if keyword:
        params["keyword"] = keyword
    if language:
        params["language"] = language
    if name:
        params["name"] = convert.join_list(" ", name)
    if open_now:
        params["opennow"] = "true"
    if rank_by:
        params["rankby"] = rank_by
    if type:
        params["type"] = type
    if region:
        params["region"] = region
    if page_token:
        params["pagetoken"] = page_token

    url = "/maps/api/place/%ssearch/json" % url_part
    return client._request(url, params)


def places(client, query, location=None, radius=None, language=None,
           min_price=None, max_price=None, open_now=False, type=None, region=None,
           page_token=None):
    """
    Places search.
    :param query: The text string on which to search, for example: "restaurant".
    :type query: string
    :param location: The latitude/longitude value for which you wish to obtain the
        closest, human-readable address.
    :type location: string, dict, list, or tuple
    :param radius: Distance in meters within which to bias results.
    :type radius: int
    :param language: The language in which to return results.
    :type language: string
    :param min_price: Restricts results to only those places with no less than
        this price level. Valid values are in the range from 0 (most affordable)
        to 4 (most expensive).
    :type min_price: int
    :param max_price: Restricts results to only those places with no greater
        than this price level. Valid values are in the range from 0 (most
        affordable) to 4 (most expensive).
    :type max_price: int
    :param open_now: Return only those places that are open for business at
        the time the query is sent.
    :type open_now: bool
    :param type: Restricts the results to places matching the specified type.
        The full list of supported types is available here:
        https://developers.google.com/places/supported_types
    :type type: string
    :param region: The region code, optional parameter.
        See more @ https://developers.google.com/places/web-service/search
    :type region: string
    :param page_token: Token from a previous search that when provided will
        returns the next page of results for the same search.
    :type page_token: string
    :rtype: result dict with the following keys:
        results: list of places
        html_attributions: set of attributions which must be displayed
        next_page_token: token for retrieving the next page of results
    """
    return _places(client, "text", query=query, location=location,
                   radius=radius, language=language, min_price=min_price,
                   max_price=max_price, open_now=open_now, type=type, region=region,
                   page_token=page_token)


def main():
    
    gmaps = googlemaps.Client(key='')

    g = geocoder.ip('me')

    latlng = g.latlng

    # latlng = [39.947141, -105.056640] #Broomfield, CO
    # latlng = [40.005657, -105.264368] #Boulder, CO

    american = places(gmaps, "american food", latlng)
    pizza = places(gmaps, "pizza", latlng)
    italian = places(gmaps, "italian food", latlng)
    chinese = places(gmaps, "chinese food", latlng)
    mexican = places(gmaps, "mexican food", latlng)
    indian = places(gmaps, "indian food", latlng)
    sandwiches = places(gmaps, "sandwiches", latlng)


	# print(latlng)

    with open('American.csv', mode='w', newline='') as csv_file:
	    fieldnames = ['name', 'rating', 'address', 'distance']
	    writer = csv.writer(csv_file, delimiter='"')

	    for i in range(20):
	    	distance = haversine(latlng[0], latlng[1], american['results'][i]['geometry']['location']['lat'], american['results'][i]['geometry']['location']['lng'])
	    	writer.writerow([american['results'][i]['name'], american['results'][i]['rating'], american['results'][i]['formatted_address'], distance])
		

    with open('Pizza.csv', mode='w', newline='') as csv_file:
	    fieldnames = ['name', 'rating', 'address', 'distance']
	    writer = csv.writer(csv_file, delimiter='"')

	    for i in range(20):
	    	distance = haversine(latlng[0], latlng[1], pizza['results'][i]['geometry']['location']['lat'], pizza['results'][i]['geometry']['location']['lng'])
	    	writer.writerow([pizza['results'][i]['name'], pizza['results'][i]['rating'], pizza['results'][i]['formatted_address'], distance])

    with open('Italian.csv', mode='w', newline='') as csv_file:
	    fieldnames = ['name', 'rating', 'address', 'distance']
	    writer = csv.writer(csv_file, delimiter='"')

	    for i in range(20):
	    	distance = haversine(latlng[0], latlng[1], italian['results'][i]['geometry']['location']['lat'], italian['results'][i]['geometry']['location']['lng'])
	    	writer.writerow([italian['results'][i]['name'], italian['results'][i]['rating'], italian['results'][i]['formatted_address'], distance])
	

    with open('Chinese.csv', mode='w', newline='') as csv_file:
	    fieldnames = ['name', 'rating', 'address', 'distance']
	    writer = csv.writer(csv_file, delimiter='"')

	    for i in range(20):
	    	distance = haversine(latlng[0], latlng[1], chinese['results'][i]['geometry']['location']['lat'], chinese['results'][i]['geometry']['location']['lng'])
	    	writer.writerow([chinese['results'][i]['name'], chinese['results'][i]['rating'], chinese['results'][i]['formatted_address'], distance])

    with open('Mexican.csv', mode='w', newline='') as csv_file:
	    fieldnames = ['name', 'rating', 'address', 'distance']
	    writer = csv.writer(csv_file, delimiter='"')

	    for i in range(20):
	    	distance = haversine(latlng[0], latlng[1], mexican['results'][i]['geometry']['location']['lat'], mexican['results'][i]['geometry']['location']['lng'])
	    	writer.writerow([mexican['results'][i]['name'], mexican['results'][i]['rating'], mexican['results'][i]['formatted_address'], distance])


    with open('Indian.csv', mode='w', newline='') as csv_file:
	    fieldnames = ['name', 'rating', 'address', 'distance']
	    writer = csv.writer(csv_file, delimiter='"')

	    for i in range(20):
	    	distance = haversine(latlng[0], latlng[1], indian['results'][i]['geometry']['location']['lat'], indian['results'][i]['geometry']['location']['lng'])
	    	writer.writerow([indian['results'][i]['name'], indian['results'][i]['rating'], indian['results'][i]['formatted_address'], distance])

    with open('Sandwiches.csv', mode='w', newline='') as csv_file:
	    fieldnames = ['name', 'rating', 'address', 'distance']
	    writer = csv.writer(csv_file, delimiter='"')

	    for i in range(20):
	    	distance = haversine(latlng[0], latlng[1], sandwiches['results'][i]['geometry']['location']['lat'], sandwiches['results'][i]['geometry']['location']['lng'])
	    	writer.writerow([sandwiches['results'][i]['name'], sandwiches['results'][i]['rating'], sandwiches['results'][i]['formatted_address'], distance])
	

    #done gathering data. Run C++ program


    # testRestaurant = "River and Woods"

    # os.system("a.exe " + testRestaurant)


if __name__ == '__main__':
	main()