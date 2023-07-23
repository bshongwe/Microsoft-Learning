# Introduction to the Microsoft Dataverse Web API

## Web API vs. the Organization service
The two main ways to interact with data and metadata in Microsoft Dataverse are the Web API and the organization service. You can use the organization service when writing plug-ins or workflow extensions by using the .NET Framework SDK assemblies that are provided by Microsoft. 

At the time of this writing, all data operations go through the underlying organization service. As such, the Web API allows you to perform the same operations as the organization service but in a RESTful style. (More information on REST will be provided later in this module.)

The following graphic is a decision tree that can help you determine when to use the Web API versus the organization service (through SDK Assemblies) and also when to use XRM Tooling Assemblies (available from Microsoft) for Windows applications. 

Decision tree to help determine when to use the Web API versus the Organization Service and also when to use X R M Tooling Assemblies for Windows applications. 

This module focuses on the Web API. For more information on the organization service, see Use the Dataverse Organization service in the Dataverse Developer Guide. 

If you'd like to learn more about the XRM Tooling Assemblies that are available for Windows client applications, see Build Windows client applications using the XRM tools, also in the Dataverse Developer Guide. XRM is considered the predecessor to Dataverse, so you'll frequently see this name embedded into documentation and tooling that is provided by Microsoft. 

## OData 4.0
Dataverse Web API is implemented as an OData (OASIS Open Data Protocol) service. By using an industry standard such as this, you're provided all the benefits of open standard development, such as cross-platform compatibility and simple implementation against a common, predefined protocol.

Dataverse doesn't provide specific .NET assembly tooling for the Web API. Instead, we recommend that you use community libraries that conform to the OData protocol. If you want more information about which libraries exist, see https://www.odata.org/libraries/. 

OData lets you interact with Dataverse data with CRUD operations that are available through standard GET, POST, PATCH, and DELETE HTTP methods. (More information about these methods will be provided later in this module.) You can also perform almost any other operation that is exposed through Dataverse Event Framework by invoking an OData function or action that has the same name as its corresponding organization service message. CRUD-related messages are the only ones that are not available, because those messages are achieved with the previously described standard HTTP methods.

## REST
Fundamentally, OData protocol is a set of RESTful (REpresentational State Transfer) APIs, a time-tested industry standard for providing interoperability between systems. REST consists of six guiding principles that restrict the way that a service can process and respond to requests to ensure that non-functional properties of that service are met (such as performance, scalability, simplicity, reliability, and so on).

For the purposes of this lesson, you should keep in mind that OData conforms to these constraints and that the Dataverse Web API in turn also conforms to the constraints because it implements the OData 4.0 protocol.

## FetchXML
FetchXML is a robust query language that allows for complex querying of Dataverse data. Microsoft provides a way for users to run FetchXML queries within a Web API query. This approach can be valuable if you encounter a scenario where FetchXML is a better fit for your particular query versus using OData query syntax. More information about FetchXML is provided in a later unit in this module.

## Authenticate against Microsoft Dataverse by using OAuth

Microsoft's Microsoft Dataverse uses OAuth 2.0 as its authentication standard. OAuth 2.0 provides an industry-standard for authenticating client applications and granting them access to a resource.

## Authentication vs. authorization
Authentication is the process or action of verifying the identity of a user or process. Microsoft's solution to this verification process is Azure Active Directory (Azure AD). Azure AD supports many options to verify the identity of a user or process. Abstracting your identity provider allows for a good separation of concerns because managing usernames and passwords can be a difficult (and risky) process.

Authorization is the process or action of verifying whether an authenticated user is authorized to access the resources that are being provided. Presently, Dataverse authorization is at the Azure AD tenant level, while management of the detailed permissions is delegated to the application based on the current signed-in user. Therefore, you won't use OAuth 2.0 to govern app-level security, which is instead handled with the Power Apps admin center.

If you want to learn more about the concepts of authentication and authorization, see Authentication basics.

## Register Dataverse apps with Azure AD
To successfully connect to your Dataverse, you must first register an app with Azure Active Directory, which can be completed in the Azure portal. Depending on the type of app that you want to make, a few different settings are available for you to configure (web apps versus native apps that are installed natively on a device). For more information on settings that are required for each of these types, see Types of app registration.

To register an app with Azure AD, you can go to the App Registrations section of the Azure Active Directory menu blade and then select New Registration.

Screenshot of App Registrations section of Azure Active Directory menu and New Registration selected.

Specify the name of your app and what type of account access you need. If you're registering a web app, specify a Redirect URI by going to the Authentication section, setting the type to Web, and then entering a redirect URI.

The following list summarizes when to use the different account types:

    Accounts in this organizational directory only (Single tenant)

    All user and guest accounts in your directory can use your application or API.

    Use this option if your target audience is internal to your organization.

    Accounts in any organizational directory (Any Azure AD directory - Multitenant)

    All users with a work or school account from Microsoft can use your application or API, including schools and businesses that use Microsoft 365.

    Use this option if your target audience is business or educational customers and to enable multitenancy.

    Accounts in any organizational directory (Any Azure AD directory - Multitenant) and personal Microsoft accounts (for example, Skype and Xbox)


All users with a work, school, or personal Microsoft account can use your application or API. It includes schools and businesses that use Microsoft 365 and personal accounts that are used to sign in to services like Xbox and Skype.

Depending on the complexity of your application setup, you might want to configure other authentication settings. Refer to the Azure Active Directory documentation for steps on how to complete this task.

## Access Dataverse using the Web API
All access to Dataverse is done in the context of a signed-in user. This can be a normal interactive user or a non-interactive user using Server-to-Server (S2S) authentication.

When an application accesses Dataverse on behalf of an interactive user the registered application must be configured with API permissions to access Dataverse with delegated permission. When an application directly accesses Dataverse, an Application User associated with the Azure AD application registration must be created in Dataverse. When using S2S authentication, Dataverse API delegated permissions isn't required.

In all cases, the authenticated users must have security roles associated with the user permitting the operations being performed using the Web API.

## Configure API permissions
If your application will be accessing Dataverse on behalf of a signed in user, go to the API permissions tab on the application registered and ensure that your application is granted user impersonation access to your Dataverse environment.

The label says Dynamics CRM, which is a historical name of the precursor product to Dataverse.

## Configure a Dataverse application user
When using S2S authentication a Dataverse Application User must be configured in each Dataverse environment, you'll be accessing with the Web API.

    Configuration of Dataverse Application Users is done from the Power Platform admin center as a System Administrator.

    From the admin center you can perform the following steps

    Create a new application user

    Associate the application user with the Azure AD app or managed identity

    Configure which Dataverse security roles will apply

    For more detailed step-by-step review Manage application users in the Power Platform admin center.

## Use authentication libraries to connect
Once your application is registered use one of the Microsoft identity platform authentication libraries to perform authentication and acquire an access token for use with the Web API.

The following is an excerpt from the Enhanced QuickStart sample that uses the Microsoft Authentication Library (MSAL). The following OAuthMessageHandler class implements a class derived from DelegatingHandler which will be passed to the constructor of the HttpClient. This handler will allow you to override the HttpClient.SendAsync method so that the access token will be refreshed by the AcquireToken* method calls with each request sent by the Http client.