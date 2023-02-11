Create Database SystemFarm

use SystemFarm

Create Table Userr
(
UserEmail Varchar(50) primary key ,
F_name varchar(20),
L_name varchar(20),
Phone bigint, 
Password int 

)
Create Table Farm
(
Position varchar(30) primary Key
)

Create Table Userr_Farm
(
Position varchar(30)  references Farm(Position),
Userr_Eamil Varchar(50) references Userr(UserEmail),
Primary key(Position)
)

Create Table  Soil
(
Soil_Type varchar(20) primary key ,
Rain varchar(10),
Humioidity varchar(20),
Crop_Prodiction varchar(20)
)

Create Table Soil_Fram
(
Soil_Type varchar(20) references Soil(Soil_Type),
Position varchar(30) references Farm(Position),
primary key(Soil_Type)
)


Create Table Plant
(
Plant_Id int Primary Key,
Plant_Name varchar(20)
)
Create Table Plant_Soil
(
Plant_Id int references Plant(Plant_Id),
Soil_Type varchar(20)  references Soil(Soil_Type),
primary key(Plant_Id)
)

Create Table Diseases
(
Dis_Id int primary key,
Dis_Name varchar(20)

)
Create Table Plant_Diseases
(
Dis_Id int  references Diseases(Dis_Id),
Plant_Id int references Plant(Plant_Id),
Primary key(Dis_Id)
)
Create  Table Admin
(
Ad_Email Varchar(50) primary key ,
Ad_Password int 
)
Create Table Treatment
(
Traet_Id  int  ,
Text varchar(10),
Ad_Email Varchar(50) references Admin(Ad_Email),
primary key(Traet_Id,Ad_Email)
)
Create Table Admin_Fram
(
Position varchar(30)  references Farm(Position),
Ad_Email Varchar(50) references Admin(Ad_Email),
primary key(Position)
)
Create Table Userr_Admin
(
Userr_Eamil Varchar(50) references Userr(UserEmail),
Ad_Email Varchar(50) references Admin(Ad_Email),
primary key(Userr_Eamil)
)



































