/*************************************************
* Data Store Source File                         *
* (C) 1999-2006 The Botan Project                *
*************************************************/

#include <botan/datastor.h>
#include <botan/filters.h>
#include <botan/parsing.h>
#include <botan/stl_util.h>

namespace Botan {

/*************************************************
* Default Matcher transform operation (identity) *
*************************************************/
std::pair<std::string, std::string>
Data_Store::Matcher::transform(const std::string& key,
                               const std::string& value) const
   {
   return std::make_pair(key, value);
   }

/*************************************************
* Data_Store Equality Comparison                 *
*************************************************/
bool Data_Store::operator==(const Data_Store& other) const
   {
   return (contents == other.contents);
   }

/*************************************************
* Search based on an arbitrary predicate         *
*************************************************/
std::multimap<std::string, std::string>
Data_Store::get(const Matcher& matcher) const
   {
   std::multimap<std::string, std::string> out;

   std::multimap<std::string, std::string>::const_iterator i;
   i = contents.begin();
   while(i != contents.end())
      {
      if(matcher(i->first, i->second))
         out.insert(matcher.transform(i->first, i->second));
      ++i;
      }

   return out;
   }

/*************************************************
* Search based on an key equality                *
*************************************************/
std::vector<std::string> Data_Store::get(const std::string& looking_for) const
   {
   std::vector<std::string> out;

   std::multimap<std::string, std::string>::const_iterator i;
   i = contents.begin();
   while(i != contents.end())
      {
      if(i->first == looking_for)
         out.push_back(i->second);
      ++i;
      }

   return out;
   }

/*************************************************
* Get a single atom                              *
*************************************************/
std::string Data_Store::get1(const std::string& key) const
   {
   std::vector<std::string> vals = get(key);

   if(vals.empty())
      throw Invalid_State("Data_Store::get1: Not values for " + key);
   if(vals.size() > 1)
      throw Invalid_State("Data_Store::get1: More than one value for " + key);

   return vals.at(0);
   }

/*************************************************
* Get a single MemoryVector atom                 *
*************************************************/
MemoryVector<byte>
Data_Store::get1_memvec(const std::string& key) const
   {
   std::vector<std::string> vals = get(key);

   if(vals.size() > 1)
      throw Invalid_State("Data_Store::get1_memvec: Multiple values for " +
                          key);

   if(vals.empty())
      return MemoryVector<byte>();

   Pipe pipe(new Hex_Decoder(FULL_CHECK));
   pipe.start_msg();
   if(vals.size())
      pipe.write(vals[0]);
   pipe.end_msg();
   return pipe.read_all();
   }

/*************************************************
* Get a single u32bit atom                       *
*************************************************/
u32bit Data_Store::get1_u32bit(const std::string& key,
                               u32bit default_val) const
   {
   std::vector<std::string> vals = get(key);

   if(vals.empty())
      return default_val;
   else if(vals.size() > 1)
      throw Invalid_State("Data_Store::get1_u32bit: Multiple values for " +
                          key);

   return to_u32bit(vals[0]);
   }

/*************************************************
* Insert a single key and value                  *
*************************************************/
void Data_Store::add(const std::string& key, const std::string& val)
   {
   multimap_insert(contents, key, val);
   }

/*************************************************
* Insert a single key and value                  *
*************************************************/
void Data_Store::add(const std::string& key, u32bit val)
   {
   add(key, to_string(val));
   }

/*************************************************
* Insert a single key and value                  *
*************************************************/
void Data_Store::add(const std::string& key, const MemoryRegion<byte>& val)
   {
   Pipe pipe(new Hex_Encoder);
   pipe.process_msg(val);
   add(key, pipe.read_all_as_string());
   }

/*************************************************
* Insert a mapping of key/value pairs            *
*************************************************/
void Data_Store::add(const std::multimap<std::string, std::string>& in)
   {
   std::multimap<std::string, std::string>::const_iterator i = in.begin();
   while(i != in.end())
      {
      contents.insert(*i);
      ++i;
      }
   }

}
