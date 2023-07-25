# Manage container properties and metadata by using .NET

Blob containers support system properties and user-defined metadata, in addition to the data they contain.

### System properties:

    System properties exist on each Blob storage resource. Some of them can be read or set, while others are read-only. Under the covers, some system properties correspond to certain standard HTTP headers. The Azure Storage client library for .NET maintains these properties for you.

### User-defined metadata:

    User-defined metadata consists of one or more name-value pairs that you specify for a Blob storage resource. You can use metadata to store additional values with the resource. Metadata values are for your own purposes only, and do not affect how the resource behaves.

    Metadata name/value pairs are valid HTTP headers, and so should adhere to all restrictions governing HTTP headers. Metadata names must be valid HTTP header names and valid C# identifiers, may contain only ASCII characters, and should be treated as case-insensitive. Metadata values containing non-ASCII characters should be Base64-encoded or URL-encoded.

### Retrieve container properties
To retrieve container properties, call one of the following methods of the BlobContainerClient class:

    GetProperties
    GetPropertiesAsync

The following code example fetches a container's system properties and writes some property values to a console window:

C#

Copy
<code>private static async Task ReadContainerPropertiesAsync(BlobContainerClient container)
{
    try
    {
        // Fetch some container properties and write out their values.
        var properties = await container.GetPropertiesAsync();
        Console.WriteLine($"Properties for container {container.Uri}");
        Console.WriteLine($"Public access level: {properties.Value.PublicAccess}");
        Console.WriteLine($"Last modified time in UTC: {properties.Value.LastModified}");
    }
    catch (RequestFailedException e)
    {
        Console.WriteLine($"HTTP error code {e.Status}: {e.ErrorCode}");
        Console.WriteLine(e.Message);
        Console.ReadLine();
    }
}</code>

### Set and retrieve metadata
    You can specify metadata as one or more name-value pairs on a blob or container resource. To set metadata, add name-value pairs to an IDictionary object, and then call one of the following methods of the BlobContainerClient class to write the values:

## SetMetadata
### SetMetadataAsync
    The name of your metadata must conform to the naming conventions for C# identifiers. Metadata names preserve the case with which they were created, but are case-insensitive when set or read. If two or more metadata headers with the same name are submitted for a resource, Blob storage comma-separates and concatenates the two values and returns HTTP response code 200 (OK).

    The following code example sets metadata on a container.

C#

Copy
<code>public static async Task AddContainerMetadataAsync(BlobContainerClient container)
{
    try
    {
        IDictionary<string, string> metadata =
           new Dictionary<string, string>();

        // Add some metadata to the container.
        metadata.Add("docType", "textDocuments");
        metadata.Add("category", "guidance");

        // Set the container's metadata.
        await container.SetMetadataAsync(metadata);
    }
    catch (RequestFailedException e)
    {
        Console.WriteLine($"HTTP error code {e.Status}: {e.ErrorCode}");
        Console.WriteLine(e.Message);
        Console.ReadLine();
    }
}</code>

    The GetProperties and GetPropertiesAsync methods are used to retrieve metadata in addition to properties as shown earlier.

    The following code example retrieves metadata from a container.

C#

Copy
<code>public static async Task ReadContainerMetadataAsync(BlobContainerClient container)
{
    try
    {
        var properties = await container.GetPropertiesAsync();

        // Enumerate the container's metadata.
        Console.WriteLine("Container metadata:");
        foreach (var metadataItem in properties.Value.Metadata)
        {
            Console.WriteLine($"\tKey: {metadataItem.Key}");
            Console.WriteLine($"\tValue: {metadataItem.Value}");
        }
    }
    catch (RequestFailedException e)
    {
        Console.WriteLine($"HTTP error code {e.Status}: {e.ErrorCode}");
        Console.WriteLine(e.Message);
        Console.ReadLine();
    }
}</code>


## Set and retrieve properties and metadata for blob resources by using REST
    Containers and blobs support custom metadata, represented as HTTP headers. Metadata headers can be set on a request that creates a new container or blob resource, or on a request that explicitly creates a property on an existing resource.

    Metadata header format
    Metadata headers are name/value pairs. The format for the header is:


Copy
<code>x-ms-meta-name:string-value</code>

    Beginning with version 2009-09-19, metadata names must adhere to the naming rules for C# identifiers.

    Names are case-insensitive. Note that metadata names preserve the case with which they were created, but are case-insensitive when set or read. If two or more metadata headers with the same name are submitted for a resource, the Blob service returns status code 400 (Bad Request).

    The metadata consists of name/value pairs. The total size of all metadata pairs can be up to 8KB in size.

    Metadata name/value pairs are valid HTTP headers, and so they adhere to all restrictions governing HTTP headers.

## Operations on metadata
    Metadata on a blob or container resource can be retrieved or set directly, without returning or altering the content of the resource.

    Note that metadata values can only be read or written in full; partial updates are not supported. Setting metadata on a resource overwrites any existing metadata values for that resource.

## Retrieving properties and metadata
    The GET and HEAD operations both retrieve metadata headers for the specified container or blob. These operations return headers only; they do not return a response body. The URI syntax for retrieving metadata headers on a container is as follows:


Copy
<code>GET/HEAD https://myaccount.blob.core.windows.net/mycontainer?restype=container</code>

The URI syntax for retrieving metadata headers on a blob is as follows:


Copy
<code>GET/HEAD https://myaccount.blob.core.windows.net/mycontainer/myblob?comp=metadata</code>

## Setting Metadata Headers
    The PUT operation sets metadata headers on the specified container or blob, overwriting any existing metadata on the resource. Calling PUT without any headers on the request clears all existing metadata on the resource.

    The URI syntax for setting metadata headers on a container is as follows:


Copy
<code>PUT https://myaccount.blob.core.windows.net/mycontainer?comp=metadata&restype=container</code>

The URI syntax for setting metadata headers on a blob is as follows:


Copy
<code>PUT https://myaccount.blob.core.windows.net/mycontainer/myblob?comp=metadata</code>

## Standard HTTP properties for containers and blobs
    Containers and blobs also support certain standard HTTP properties. Properties and metadata are both represented as standard HTTP headers; the difference between them is in the naming of the headers. Metadata headers are named with the header prefix x-ms-meta- and a custom name. Property headers use standard HTTP header names, as specified in the Header Field Definitions section 14 of the HTTP/1.1 protocol specification.

The standard HTTP headers supported on containers include:

## ETag
Last-Modified
The standard HTTP headers supported on blobs include:

    ETag
    Last-Modified
    Content-Length
    Content-Type
    Content-MD5
    Content-Encoding
    Content-Language
    Cache-Control
    Origin
    Range
