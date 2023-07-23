# Use OData to query data
OData is a time-tested language for querying RESTful APIs. This lesson explores a few ways of performing CRUD operations against Microsoft Dataverse data.


## Create records
To create records, use the HTTP POST method.


## Retrieve records
To retrieve records, use the HTTP GET method.
The following sample retrieves an account with the ID of 00000000-0000-0000-0000-000000000001:


## Update records
Depending on what you are trying to accomplish, you can choose between one of two methods for updating records:

If you're performing an update of multiple attribute values, use the HTTP PATCH method. PATCH methods provide upsert capability if you provide an ID value as part of your request, a beneficial feature when you're synchronizing data between systems.

If you're updating a single attribute value, use the HTTP PUT method. This method can't be used with navigation properties like lookups because that requires a reference to be removed as well.

If you want to retrieve data from the entity that you're updating, you can use the return=representation request header. If you want to control which properties are returned, you can add a $select query to your PATCH URL. In the following example, the header has been added and the $select has been amended to only include the name, creditonhold, and address1 attributes.

The following is a sample PUT request where an account's name for a given record is updated:
<code>PUT [Organization URI]/api/data/v9.2/accounts(00000000-0000-0000-0000-000000000001)/name HTTP/1.1  
Content-Type: application/json  
OData-MaxVersion: 4.0  
OData-Version: 4.0  
  
{"value": "Updated Sample Account Name"}</code>
