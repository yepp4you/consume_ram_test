/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/serialize.hpp>
#include <string>

namespace tic_tac_toe {
   static const account_name games_account = N(games);
   static const account_name code_account = N(tic.tac.toe);

   /**
    * @brief Action to create new game
    */
    struct transfer {
       account_name from;
       account_name to;
       eosio::asset        quantity;
       std::string       memo;
       EOSLIB_SERIALIZE(transfer, (from)(to)(quantity)(memo) )
    };

    struct game {
        account_name   gamer;
        uint64_t       record;
        uint64_t primary_key()const { return gamer; }
    };

   typedef eosio::multi_index< games_account, game> games;
}
/// @}
