create database if not exists sahay;
use sahay;

create table if not exists locations (
    id int auto_increment primary key,
    name varchar(100) not null,
    type varchar(50) not null,
    latitude decimal(10, 6) not null,
    longitude decimal(10, 6) not null,
    population int not null
);

create table if not exists roads (
    id int auto_increment primary key,
    from_id int not null,
    to_id int not null,
    distance decimal(8, 2) not null,
    road_type varchar(50) not null,
    is_one_way int default 0,
    foreign key (from_id) references locations(id),
    foreign key (to_id) references locations(id)
);

create table if not exists road_conditions (
    id int auto_increment primary key,
    road_id int not null unique,
    water_level decimal(5, 2) default 0.00,
    traffic int default 0,
    flood_severity int default 0,
    landslide_risk int default 0,
    road_damage int default 0,
    blocked int default 0,
    last_updated timestamp default current_timestamp on update current_timestamp,
    foreign key (road_id) references roads(id) on delete cascade
);

create table if not exists households (
    id int auto_increment primary key,
    location_id int not null,
    address varchar(255) not null,
    members int not null,
    phone varchar(20),
    foreign key (location_id) references locations(id)
);

create table if not exists people (
    id int auto_increment primary key,
    household_id int not null,
    name varchar(100) not null,
    age int not null,
    weak int default 0,
    status varchar(50) default 'Safe',
    foreign key (household_id) references households(id) on delete cascade
);

create table if not exists hospitals (
    id int auto_increment primary key,
    location_id int not null,
    name varchar(150) not null,
    available_beds int not null,
    contact varchar(50),
    foreign key (location_id) references locations(id)
);

create table if not exists rescue_teams (
    id int auto_increment primary key,
    name varchar(100) not null,
    team_type varchar(50) not null,
    current_location_id int not null,
    available int default 1,
    foreign key (current_location_id) references locations(id)
);

create table if not exists rescue_team_members (
    id int auto_increment primary key,
    rescue_team_id int not null,
    member_name varchar(100) not null,
    role varchar(100) not null,
    foreign key (rescue_team_id) references rescue_teams(id) on delete cascade
);

create table if not exists shelters (
    id int auto_increment primary key,
    location_id int not null,
    name varchar(150) not null,
    capacity int not null,
    occupied int default 0,
    foreign key (location_id) references locations(id)
);

create table if not exists disasters (
    id int auto_increment primary key,
    disaster_type varchar(50) not null,
    location_id int not null,
    severity int not null,
    description text,
    status varchar(20) default 'Active',
    created_at timestamp default current_timestamp,
    foreign key (location_id) references locations(id)
);
