# Interact with Microsoft Dataverse Web API by using Postman

Postman is a valuable tool to use for composing ad hoc Web API queries and verifying the behavior of Web API Operations without having to write a program to do so. If you're new to Postman, see the First 5 things to try if you're new to Postman article for an introduction to the topic.

## Register an app in Azure Active Directory
To connect Postman to Microsoft Dataverse, you must first ensure that you have an application registered in your Azure AD environment.

Get the current version of your Web API endpoint
You can find the version number of your Web API endpoint by going to your environment's Developer resources in the maker portal.

From the Developer Resources page. Your version number will be indicated under the Web API endpoint, as shown in the following image. Make note of the endpoint and the version.


## Set up Postman
To start the setup process, install Postman.

After Postman has been installed, you'll use a feature that Postman has to manage environment variables so that you can cleanly manage entities such as your endpoint URLs and client IDs.

To create a Postman environment that you can use to connect with your Dataverse instance, follow these steps:

Launch the Postman desktop application.

Select the Environment Options gear icon in the top-right corner.

In the Manage Environments dialog box, select the Add button to add a new environment.

In the dialog box that opens, enter a name for the environment and then add the following key/value pairs into the editing space.

## Variable	Initial value
url	https://[ORGANIZATION].api.crm.dynamics.com
clientid	51f81489-12ee-4a9e-aaae-a2591f45987d
version	9.2
webapiurl	{{url}}/api/data/v{{version}}/
callback	https://callbackurl
authurl	https://login.microsoftonline.com/common/oauth2/authorize?resource={{url}}


Replace the instance URL placeholder value with the URL of your Dataverse environment and then select Add to save the environment.

Close the Manage environments dialog box.

## Generate an access token to use with your environment
To connect by using OAuth 2.0, you must have an access token. To get a new access token, follow these steps:

Make sure that the new environment you created is selected.

Select the Authorization tab.

Set the Type to OAuth 2.0.

Verify that you've selected the environment that you created.

Scroll down to the Configure New Token pane.

Set the following values in the dialog box. Select Implicit from the Grant Type drop-down menu. You can set the Token Name to whatever you like and then leave other keys set to default values.

 Note

If you are configuring environments in Postman for multiple Dataverse instances by using different user credentials, you might need to delete the cookies that are cached by Postman. Select the Cookies link, which can be found under the Send button, and remove the saved cookies from the Manage Cookies dialog box.

Some of these cookies are persistent. You can delete some cookies in groups, but you might have to delete others individually. You might need to complete this process twice to ensure that no cookies remain.

Select Request Token. When you make this selection, an Azure Active Directory sign-in page appears. Enter your username and password.

After the token is generated, scroll to the bottom and select Use Token. This selection closes the Manage Access Tokens dialog box.

After you've added a token, you can select which token to apply to requests. On the Available Tokens drop-down list, select the token that you've created. The Authorization header will be added to the Web API request.

## Test your connection
Create a new Web API request to test the connection with your Common Data Service instance. Use the WhoAmI function by following these steps:

Select GET as the HTTP method and add {{webapiurl}}WhoAmI in the editing space.

Screenshot of GET HTTP as method and WhoAmI added in editing space.

Select Send to send this request.

If your request is successful, you'll see the data from the WhoAmIResponse ComplexType that is returned by the WhoAmI Function.

