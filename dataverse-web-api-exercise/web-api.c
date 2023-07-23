// #1. Use authentication libraries to connect
class OAuthMessageHandler : DelegatingHandler

{

private AuthenticationHeaderValue authHeader;

public OAuthMessageHandler(string serviceUrl, string clientId, string redirectUrl, string username, string password,

HttpMessageHandler innerHandler)

: base(innerHandler)

{

//Build Microsoft.Identity.Client (MSAL) OAuth Token Request

var authBuilder = PublicClientApplicationBuilder.Create(clientId)

.WithAuthority(AadAuthorityAudience.AzureAdMultipleOrgs)

.WithRedirectUri(redirectUrl)

.Build();

var scope = serviceUrl + "//.default";

string[] scopes = { scope };

AuthenticationResult authBuilderResult;

if (username != string.Empty && password != string.Empty)

{

//Make silent Microsoft.Identity.Client (MSAL) OAuth Token Request

var securePassword = new SecureString();

foreach (char ch in password) securePassword.AppendChar(ch);

authBuilderResult = authBuilder.AcquireTokenByUsernamePassword(scopes, username, securePassword)

.ExecuteAsync().Result;

}

else

{

//Popup authentication dialog box to get token

authBuilderResult = authBuilder.AcquireTokenInteractive(scopes)

.ExecuteAsync().Result;

}

//Note that an Azure AD access token has finite lifetime, default expiration is 60 minutes.

authHeader = new AuthenticationHeaderValue("Bearer", authBuilderResult.AccessToken);

}

protected override Task<HttpResponseMessage> SendAsync(

HttpRequestMessage request, System.Threading.CancellationToken cancellationToken)

{

request.Headers.Authorization = authHeader;

return base.SendAsync(request, cancellationToken);

}

}


// #2. You could then have a helper method to get the HttpClient instance using the handler
static HttpClient GetHttpClient(string url, string clientId, string redirectUrl, string version = "v9.2")

{

try

{

HttpMessageHandler messageHandler = new OAuthMessageHandler(url, clientId, redirectUrl, \"\", \"\",

new HttpClientHandler());

HttpClient httpClient = new HttpClient(messageHandler)

{

BaseAddress = new Uri(string.Format("{0}/api/data/{1}/", url, version)),

Timeout = new TimeSpan(0, 2, 0) //2 minutes

};

return httpClient;

}

catch (Exception)

{

throw;

}

}


// #3. And finally, using the client instance to make a Web API call
using (HttpClient client = GetHttpClient("https://yourenvname.api.crm.dynamics.com",

"51f81489-12ee-4a9e-aaae-a2591f45987d", "http://localhost:8080"))

{

// Use the WhoAmI function

var response = client.GetAsync("WhoAmI").Result;

if (response.IsSuccessStatusCode)

{

//Get the response content and parse it.

JObject body = JObject.Parse(response.Content.ReadAsStringAsync().Result);

Guid userId = (Guid)body["UserId"];

Console.WriteLine("Your UserId is {0}", userId);

}

else

{

Console.WriteLine("The request failed with a status of '{0}'",

response.ReasonPhrase);

}

Console.WriteLine("Press any key to exit.");

Console.ReadLine();

}


// #4. And finally, using the client instance to make a Web API call
using (HttpClient client = GetHttpClient("https://yourenvname.api.crm.dynamics.com",

"51f81489-12ee-4a9e-aaae-a2591f45987d", "http://localhost:8080"))

{

// Use the WhoAmI function

var response = client.GetAsync("WhoAmI").Result;

if (response.IsSuccessStatusCode)

{

//Get the response content and parse it.

JObject body = JObject.Parse(response.Content.ReadAsStringAsync().Result);

Guid userId = (Guid)body["UserId"];

Console.WriteLine("Your UserId is {0}", userId);

}

else

{

Console.WriteLine("The request failed with a status of '{0}'",

response.ReasonPhrase);

}

Console.WriteLine("Press any key to exit.");

Console.ReadLine();

}

