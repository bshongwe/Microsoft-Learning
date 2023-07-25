# FetchXML
    is a robust query language that was developed by Microsoft to enable complex operations to be performed against Microsoft Dataverse data. It provides considerably more filtering options than the OData connectors, and it also allows you to see the labels for reference data such as Option Set labels or lookup fields.

## You can run FetchXML queries by using the following methods:

    Dataverse Web API

    Organization service

    You can also apply a custom FetchXML filter to a lookup field within a model-driven app. This approach allows for more complex lookup scenarios that aren't easily accomplished out of the box. For more information on how to complete this process, see the addCustomFilter Client API Reference.

## Tools to help build your queries
If you're querying data against a model-driven app that is built on Dataverse, the simplest method for building FetchXML queries is to use Advanced Find, which contains a Download FetchXML function. You're limited to the UI on what filters and related data that you can pull, but it's frequently an excellent first start so that you don't have to compose the XML anew.

Another notable tool, called FetchXML Builder, can be found at XrmToolBox. With this tool, you can construct FetchXML in ways that Advanced Find can't (aggregates, outer joins, "has no" queries, and attributes from multi-level linked entities). It also provides a wealth of other features, which you can find at their website: FetchXML Builder.

## Additional resources
Go to Microsoft Learn to discover in-depth details on the FetchXML Query Language. The Use FetchXML to query data section covers several advanced topics such as how to handle paging, querying hierarchical data, and much more.
