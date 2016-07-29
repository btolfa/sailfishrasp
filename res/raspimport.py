import sqlite3
import xml.etree.ElementTree as ET
import os

conn = sqlite3.connect('rasp.db')

def create_tables():
    cur = conn.cursor()
    
    cur.execute('CREATE TABLE station(zone INTEGER, city TEXT, direction TEXT, esr INTEGER, importance INTEGER, lat REAL, lon REAL, popular_title TEXT, region TEXT, short_title TEXT, title TEXT)')
    cur.execute('CREATE TABLE settlement(zone INTEGER, geo_id INTEGER, id INTEGER, latitude REAL, longitude REAL, title TEXT)')
    cur.execute('CREATE TABLE zone(code TEXT, id INTEGER, settlement_id INTEGER, settlement_title TEXT, title TEXT)')
    
    conn.commit()

def import_zones():
    tree = ET.parse('all_suburban_zones.xml')
    root = tree.getroot();
    
    cur = conn.cursor()
    for zone in root:
        cur.execute('insert into zone({}) values({})'.format(
            ', '.join(zone.attrib.keys()),
            ', '.join([':'+ x for x in zone.attrib.keys()])),
        zone.attrib)

        for settlement in zone:
            settlement.attrib['zone'] = zone.attrib['id']
            cur.execute(
                'insert into settlement({}) values({})'.format(
                    ', '.join(settlement.attrib.keys()),
                    ', '.join([':'+ x for x in settlement.attrib.keys()])),
                settlement.attrib
            )
    
    conn.commit()

def import_stations():
    cur = conn.cursor()
    
    for file in os.listdir('by-id'):
        tree = ET.parse(os.path.join('by-id', file))
        suburban_zone = tree.getroot()
        for station in suburban_zone:
            station.attrib['zone'] = suburban_zone.attrib['id']
            cur.execute('insert into station({}) values ({})'
                .format(', '.join(station.attrib.keys()),
                        ', '.join([':'+ x for x in station.attrib.keys()])),
                station.attrib
            )
    
    conn.commit()

def main():
    create_tables()
    import_zones()
    import_stations()
    

if __name__ == "__main__":
    main()