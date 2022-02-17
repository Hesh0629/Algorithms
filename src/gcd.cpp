ll gcd(ll x,ll y){
  if(!y)return x;
  return gcd(y,x%y);
}

// ax-by= gcd(a,b)의 해를 구하고 싶더라도 똑타이 ex_gcd(a,b)를 진행하면 된다.
// 당연하게도 y가 음수인 해를 구하면 되는것이기 
pair<ll,ll> ex_gcd(ll a,ll b){
  if(!b) return{1,0};
  pair<ll,ll>rec=ex_gcd(b,a%b);
  ll x=rec.second;
  ll y=rec.first-(a/b)*rec.second;
  if(x<=0){
    x+=b;
    y-=a;
  }
  return{x,y};
}
