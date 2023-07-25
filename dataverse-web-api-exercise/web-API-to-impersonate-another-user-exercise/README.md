# Use the Web API to impersonate another user
Occasionally, you might need to run logic for another user. Within the context of Microsoft Dataverse, the logic that you're running will apply all appropriate role and object-based security based on the user whom you're impersonating. This method can be especially effective when you're integrating external systems with a Dataverse solution where the integration account is a system account versus the user who actually invoked the request.

## Implement a Web API request with user impersonation
When calling any Web API method, you can provide a CallerObjectId in your message header to indicate that you want the message to be run for that particular user. The value of this parameter is their Azure Active Directory (Azure AD) object ID. The Azure Graph API provides a method to query Azure AD user data. For more information, see the Azure AD Graph API Reference.

## Determine the user who performed an operation
If you need to see the ID of the user who actually performed an operation for another user, you can query the record's createdonbehalfby value, which will contain this detail. For example, if you want to see if an account record was created through user impersonation rather than by the actual user, you could query that account record to compare their createdby and createdonbehalfby values

